#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xcb440b5e, "module_layout" },
	{ 0xe1d71654, "cdev_del" },
	{ 0xc83492ef, "kmalloc_caches" },
	{ 0xc3a1cc09, "cdev_init" },
	{ 0x2b68bd2f, "del_timer" },
	{ 0x56470118, "__warn_printk" },
	{ 0x37fd21cc, "device_destroy" },
	{ 0xc6f46339, "init_timer_key" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x15ba50a6, "jiffies" },
	{ 0x6b10bee1, "_copy_to_user" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x85401a17, "device_create" },
	{ 0x24d273d1, "add_timer" },
	{ 0x6e06a909, "init_net" },
	{ 0x3ae1c269, "nf_register_net_hook" },
	{ 0xcf8afbe8, "nf_unregister_net_hook" },
	{ 0x4c75eeab, "cdev_add" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0x92997ed8, "_printk" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xcbd4898c, "fortify_panic" },
	{ 0x8bd65ff4, "kmem_cache_alloc_trace" },
	{ 0x37a0cba, "kfree" },
	{ 0x69acdf38, "memcpy" },
	{ 0x8eab5523, "class_destroy" },
	{ 0x13c49cc2, "_copy_from_user" },
	{ 0x109c449a, "__class_create" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "19135BCA916F1160C5D1376");
