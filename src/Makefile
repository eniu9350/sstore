CC=gcc
ww=aa

rex: clean
	$(CC) --std=c99 -g -o sstore -I/usr/include -L. -L/usr/local/lib  mapex.c util.c object_framework_rex.c main.c manager_rex.c input_generator.c -lm -levent -lhiredis -lmongoc -llua

rm: clean
	$(CC) --std=c99 -g -o sstore -I/usr/include -L. -L/usr/local/lib  mapex.c util.c object_framework_rm.c main.c manager_rm.c input_generator.c -lm -levent -lhiredis -lmongoc -llua


e: clean
	$(CC) --std=c99 -I/usr/local/include -I/usr/include -L/usr/local/lib -L/usr/lib -o e e.c -lmongoc -lm -llua

l: clean
	$(CC) -o l -I/usr/local/include -I/usr/include -L/usr/local/lib -L/usr/lib l.c -lm -llua

of:
	$(CC) --std=c99 -o of -I/usr/local/include -L/usr/local/lib -L. manager_redis_mongo.c object_framework.c -lmongoc -lhiredis

clean:
	rm sstore test e l of -rf
