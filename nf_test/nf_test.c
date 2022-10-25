//'Hello World' netfilter hooks example
//For any packet, we drop it, and log fact to /var/log/messages

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/udp.h>
#include <linux/ip.h>
MODULE_LICENSE("GPL");

struct DNS_HEADER
{
    unsigned short id; // identification number

    unsigned char rd :1; // recursion desired
    unsigned char tc :1; // truncated message
    unsigned char aa :1; // authoritive answer
    unsigned char opcode :4; // purpose of message
    unsigned char qr :1; // query/response flag

    unsigned char rcode :4; // response code
    unsigned char cd :1; // checking disabled
    unsigned char ad :1; // authenticated data
    unsigned char z :1; // its z! reserved
    unsigned char ra :1; // recursion available

    unsigned short q_count; // number of question entries
    unsigned short ans_count; // number of answer entries
    unsigned short auth_count; // number of authority entries
    unsigned short add_count; // number of resource entries
};

static struct nf_hook_ops nfho;         //struct holding set of hook function options


//function to be called by hook
unsigned int hook_func(unsigned int hooknum, struct sk_buff *skb, const struct net_device *in, const struct net_device *out, int (*okfn)(struct sk_buff *))
{
  struct iphdr *ip_header = (struct iphdr*) skb_network_header(skb);
  
  if (ip_header->protocol == IPPROTO_UDP) {
     struct udphdr *udp_header = (struct udphdr *)skb_transport_header(skb);
     if (ntohs(udp_header->dest) == 53 ) {
       char *dname = ((char *)udp_header) + sizeof(struct udphdr) + sizeof(struct DNS_HEADER);
       printk(KERN_INFO"request name:%s\n", dname);
       printk(KERN_INFO"got udp packet port = %d  port = %d\n", ntohs(udp_header->dest), udp_header->dest);
       return NF_ACCEPT;
     }
  }
  return NF_ACCEPT;        
}

//Called when module loaded using 'insmod'
int nftest_init()
{
  nfho.hook = hook_func;                       //function to call when conditions below met
  nfho.hooknum = NF_INET_PRE_ROUTING;            //called right after packet recieved, first hook in Netfilter
  nfho.pf = PF_INET;                           //IPV4 packets
  nfho.priority = NF_IP_PRI_FIRST;             //set to highest priority over all other hook functions
  nf_register_hook(&nfho);                     //register hook

  printk(KERN_INFO"install netfilter");

  return 0;                                    //return 0 for success
}

//Called when module unloaded using 'rmmod'
void nftest_exit()
{
  nf_unregister_hook(&nfho);                     //cleanup – unregister hook
}

module_init(nftest_init);
module_exit(nftest_exit);
