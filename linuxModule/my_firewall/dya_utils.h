/*
 * @Author: Rio
 * @Date: 2022-08-30 19:51:44
 * @LastEditTime: 2022-08-30 19:53:35
 * @FilePath: /firewall-in-linux-module/linuxModule/my_firewall/dya_utils.h
 * @Description:
 */
#ifndef _UTILS_H_
#define _UTILS_H_

#include <linux/string.h>
// #include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/skbuff.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>

/* Utility functions */
unsigned int str_to_port(char *);
unsigned int str_to_ip(char *, int);
bool compare_ip(unsigned int, unsigned int);
bool compare_port(unsigned int, unsigned int);

#endif /* _UTILS_H_ */
