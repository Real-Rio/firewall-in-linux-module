/*
 * @Author: Rio
 * @Date: 2022-08-30 18:48:51
 * @LastEditTime: 2022-08-31 22:14:42
 * @FilePath: /firewall-in-linux-module/linuxModule/my_firewall/nl_client.h
 * @Description:头文件
 */
#ifndef _NETFLTRHOOKS_H_
#define _NETFLTRHOOKS_H_
#include <linux/kernel.h>
#include <stdio.h>
// #include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/string.h>
unsigned int str_to_port(char *);
unsigned int str_to_ip(char *, int);
void ip_to_str(unsigned int ip, char *str);
void port_to_str(unsigned int port, char *str);

#endif /* _NETFLTRHOOKS_H_ */
