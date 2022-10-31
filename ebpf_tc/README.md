# 使用方法
```sh
yum install clang llvm iproute2 
yum --enablerepo=powertools install libbpf-devel

clang -I ./headers/ -O2 -target bpf -c tc-xdp-drop-tcp.c -o tc-xdp-drop-tcp.o
docker run -d -p 80:80 --name=nginx-xdp-tc nginx:alpine
tc qdisc add dev veth09e1d2e clsact
tc filter add dev veth09e1d2e egress bpf da obj tc-xdp-drop-tcp.o sec tc
```
