so:
	gcc -Wall -fPIC -c bst.c
	gcc -shared -Wl,-soname,libctest.so.1 -o libctest.so.1.0   *.o
stat:
	gcc -Wall -L/usr/lib main.c -lctest -o meme
dyn:
	gcc -rdynamic -o lmao main1.c -ldl
