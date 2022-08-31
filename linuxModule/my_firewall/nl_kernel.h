/*
 * @Author: Rio
 * @Date: 2022-08-30 21:08:34
 * @LastEditTime: 2022-08-30 21:08:45
 * @FilePath: /firewall-in-linux-module/linuxModule/my_firewall/nl_kernel.h
 * @Description:netlink kernel's header file
 */
void nltest_krecv(struct sk_buff *skb);
int nltest_ksend(char *info, int pid);
