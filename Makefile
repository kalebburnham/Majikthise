SRCDIR = src/
TESTDIR = tests/
TESTBIN = ./test

main:
	cd $(SRCDIR) && $(MAKE)
	cd $(TESTDIR) && $(MAKE)

clean:
	cd $(SRCDIR) && $(MAKE) clean
	cd $(TESTDIR) && $(MAKE) clean

test:
	cd $(TESTDIR) && $(TESTBIN)