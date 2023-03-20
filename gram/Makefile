YACC=yacc -d
LDFLAGS=-lfl
LD=$(CC)

all: as

as: y.tab.o lex.yy.o
	$(LD) $(LDFLAGS) -o $@ $^

lex.yy.o: lex.yy.c

y.tab.o: y.tab.c

lex.yy.c: scan.l
	$(LEX) $^

y.tab.c: gram.y
	$(YACC) $^

check: all test
	./test

.PHONY: clean
clean:
	rm -f *.o
	rm -f lex.yy.c y.tab.c y.tab.h
	rm -f test
	rm -f as
