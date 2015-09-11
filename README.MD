# Tugas 1 Pengembangan Aplikasi Terdistribusi #
Oleh:

- Fahziar Riesad Wutono - 13512012
- Muhammad Reza Irvanda - 13512042

## Tools, Prosedur dan Hasil Pengujian Apache & Nginx##

### Tools Pengujian ###
Tools yang digunakan untuk melakukan pengujian adalah Apache Bench versi 2.3.

### Prosedur Pengujian ###
Berikut adalah prosedur untuk melakukan pengujian:

1. Set jumlah maksimum file yang dibuka menjadi 20000 untuk user yang mengeksekusi apache http server dan nginx.
2. Jalankan perintah `watch -n 0.1 'top -b -n1 >> top-report.txt'`. Perintah ini digunakan untuk mengambil penggunaan memory selama server dijalankan.
3. Buka terminal lain. Jalankan `ulimit -n 20000`
4. Jalankan perintah `ab -c 10000 -n 10000 <alamat host dan file uji>`. Ganti `<alamat host dan file uji>` dengan alamat yang sebenarnya.
5. Kembali ke terminal sebelumnya, hentikan perintah `watch -n 0.1 'top -b -n1 >> top-report.txt'`
6. Perhatikan penggunaan memory selama benchmark dijalankan

### Hasil Pengujian ###

#### Pengujian Apache HTTP Server ####
Hasil pengujian Apache HTTP Server; ukuran file 504 bytes

    Completed 1000 requests
    Completed 2000 requests
    Completed 3000 requests
    Completed 4000 requests
    Completed 5000 requests
    Completed 6000 requests
    Completed 7000 requests
    Completed 8000 requests
    apr_socket_recv: Connection reset by peer (104)
    Total of 8217 requests completed
    
    Memory usage 60 MB

Hasil pengujian Apache HTTP Server; ukuran file 19,7 KBytes

    Completed 1000 requests
	Completed 2000 requests
	Completed 3000 requests
	Completed 4000 requests
	Completed 5000 requests
	Completed 6000 requests
	Completed 7000 requests
	apr_socket_recv: Connection reset by peer (104)
	Total of 7318 requests completed

	Memory usage 60 MB

Dengan konfigurasi default, Apache HTTP Server tidak dapat menangani 10.000 concurrent connections.

#### Pengujian nginx ####

Hasil pengujian nginx; ukuran file 504 bytes

	Server Software:        nginx/1.4.6
	Server Hostname:        localhost
	Server Port:            80

	Document Path:          /500b.html
	Document Length:        201 bytes

	Concurrency Level:      10000
	Time taken for tests:   0.939 seconds
	Complete requests:      10000
	Failed requests:        6031
	   (Connect: 0, Receive: 0, Length: 6031, Exceptions: 0)
	Non-2xx responses:      3969
	Total transferred:      5965594 bytes
	HTML transferred:       3837393 bytes
	Requests per second:    10650.87 [#/sec] (mean)
	Time per request:       938.890 [ms] (mean)
	Time per request:       0.094 [ms] (mean, across all concurrent requests)
	Transfer rate:          6204.96 [Kbytes/sec] received

	Connection Times (ms)
    	          min  mean[+/-sd] median   max
	Connect:      142  224  48.1    220     320
	Processing:    79  265 100.8    224     482
	Waiting:       77  254 112.2    224     482
	Total:        222  489  61.0    461     624

	Percentage of the requests served within a certain time (ms)
	50%    461
	66%    504
	75%    535
	80%    552
	90%    587
	95%    600
	98%    610
	99%    620
	100%    624 (longest request)
	
	Memory usage: 406 MB

Hasil pengujian nginx; ukuran file 19,7 KBytes

    Server Software:        nginx/1.4.6
	Server Hostname:        localhost
	Server Port:            80

	Document Path:          /20kb.html
	Document Length:        20257 bytes

	Concurrency Level:      10000
	Time taken for tests:   0.828 seconds
	Complete requests:      10000
	Failed requests:        0
	Total transferred:      205010000 bytes
	HTML transferred:       202570000 bytes
	Requests per second:    12070.95 [#/sec] (mean)
	Time per request:       828.435 [ms] (mean)
	Time per request:       0.083 [ms] (mean, across all concurrent requests)
	Transfer rate:          241666.61 [Kbytes/sec] received
	
	Connection Times (ms)
    	          min  mean[+/-sd] median   max
	Connect:      131  227  50.4    229     315
	Processing:   176  243  58.6    231     386
	Waiting:      102  205  85.5    191     386
	Total:        446  470  15.9    465     519

	Percentage of the requests served within a certain time (ms)
	50%   1035
	66%   1049
	75%   1059
	80%   1064
	90%   1079
	95%   1087
	98%   1092
	99%   1093
	100%   1095 (longest request)

	Memory usage: 406 MB

Dengan konfigurasi default, Nginx mampu menerima 10.000 concurrent request baik pada file berukuran sekitar 500 bytes maupun pada file berukuran 20kB. 

## Petunjuk Building, Running dan Testing Program Web Server Sederhana ##
### Building dan Running ###

Web server ini dibuat dengan menggunakan libevent. Jika menggunakan ubuntu, pastikan package libevent-dev sudah diinstall. Pada distro lainnya, pastikan package untuk mengembangkan aplikasi dengan libevent sudah diinstal.

Untuk mem-build server, pada direktori ini jalankan perintah :
	make

Perintah ini akan menghasilkan sebuah executeable bernama 'server'.
Jalankan executeable dengan menjalankan perintah : 

	./server 

Konfigurasi server dapat dilakukan dengan mengubah isi dari config.txt,
dengan format :

	<host> <port> <root directory yang akan ditampilkan>

Misalkan pada config.txt yang default:

	0.0.0.0 5678 htdocs

### Hasil Pengujian ###
Prosedur pengujian program web server sederhana ini sama dengan prosedur pengujian web server Apache dan nginx.

Berikut hasil pengujian dengan file berukuran 504 bytes

	Server Software:
	Server Hostname:        localhost
	Server Port:            5678

	Document Path:          /500b.html
	Document Length:        504 bytes

	Concurrency Level:      10000
	Time taken for tests:   0.988 seconds
	Complete requests:      10000
	Failed requests:        0
	Total transferred:      5840000 bytes
	HTML transferred:       5040000 bytes
	Requests per second:    10123.89 [#/sec] (mean)
	Time per request:       987.763 [ms] (mean)
	Time per request:       0.099 [ms] (mean, across all concurrent requests)
	Transfer rate:          5773.78 [Kbytes/sec] received

	Connection Times (ms)
    	          min  mean[+/-sd] median   max
	Connect:      138  241  61.2    240     349
	Processing:   128  395 105.1    422     510
	Waiting:      124  394 105.4    421     509
	Total:        471  636  57.0    656     679

	Percentage of the requests served within a certain time (ms)
	50%    656
	66%    662
	75%    666
	80%    669
	90%    674
	95%    674
	98%    676
	99%    677
	100%    679 (longest request)

	Memory usage: 38 Mbytes

Berikut hasil pengujian dengan file berukuran 19,7 KBytes

	Server Software:
	Server Hostname:        localhost
	Server Port:            5678

	Document Path:          /20kb.html
	Document Length:        20257 bytes

	Concurrency Level:      10000
	Time taken for tests:   1.343 seconds
	Complete requests:      10000
	Failed requests:        0
	Keep-Alive requests:    10000
	Total transferred:      203630000 bytes
	HTML transferred:       202570000 bytes
	Requests per second:    7445.71 [#/sec] (mean)
	Time per request:       1343.055 [ms] (mean)
	Time per request:       0.134 [ms] (mean, across all concurrent requests)
	Transfer rate:          148063.50 [Kbytes/sec] received

	Connection Times (ms)
    	          min  mean[+/-sd] median   max
	Connect:      139  255  63.9    255     368
	Processing:   144  764 114.2    795     842
	Waiting:      133  574 139.1    623     660
	Total:        510 1019  87.0   1035    1095

	Percentage of the requests served within a certain time (ms)
	50%   1035
	66%   1049
	75%   1059
	80%   1064
	90%   1079
	95%   1087
	98%   1092
	99%   1093
	100%   1095 (longest request)
	
	Memory usage: 269 Mbytes

Web server sederhana yang dibuat dapat menangani 10.000 concurrent request baik dengan file berukuran sekitar 500 bytes maupun dengan file berukuran sekitar 20 kBytes. 