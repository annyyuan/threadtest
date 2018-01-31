# threadtest
c++ thread


HowTo:
./threadtest --parallel/--serial time(second) [--output]

比如说运行程序:在同一个线程内随机生成一个长度为12的包含字母和数字的字符，对这个字符串进行升序排序。
则在终端输入: ./threadtest --serial 1 表示运行该程序1秒
./threadtest --serial 1 --output 表示运行该程序1秒, 并输出所有排序过的字符串

运行程序:编写一个支持泛型的线程安全FIFO阻塞队列，采用生产和消费者模型，
一个线程随机生成一个长度为12的包含字母和数字的字符串放入队列，另一个线程从队列读取字符并按字符顺序升序排序。
则在终端输入:./threadtest --parallel 1 表示运行该程序1秒
./threadtest --parallel 1 --output 表示运行该程序1秒, 并输出所有排序过的字符串



