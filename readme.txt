编译出现:
	WARNING: "nr_threads" [/home/fengyuwuzu/myir/MYiR-iMX-Linux/drivers/loadavg/myloadavg.ko] undefined!
	WARNING: "nr_running" [/home/fengyuwuzu/myir/MYiR-iMX-Linux/drivers/loadavg/myloadavg.ko] undefined!
	WARNING: "get_avenrun" [/home/fengyuwuzu/myir/MYiR-iMX-Linux/drivers/loadavg/myloadavg.ko] undefined!
是由于内核默认没有将以上方法和变量导出成模块，需要手动导出一下

