all:
	$(MAKE) -C test/primitive_types all
	$(MAKE) -C test/exception_handling all

clean:
	$(MAKE) -C test/primitive_types clean
	$(MAKE) -C test/exception_handling clean
