ARCH=amd64

.PHONY: all
all: so/libsplunk.so

so:
	@mkdir -p so

obj:
	@mkdir -p obj

.PHONY: clean
clean:
	rm -f tests so/* obj/*

obj/logger.o: obj src/logger.c src/logger.h
	gcc -c -Wall -Werror -fpic -o obj/logger.o src/logger.c

obj/config.o: obj src/config.c src/config.h
	gcc -c -Wall -Werror -fpic -o obj/config.o src/config.c

obj/splunk.o: obj src/splunk.c src/splunk.h
	gcc -c -Wall -Werror -fpic -o obj/splunk.o src/splunk.c

so/libsplunk.so: obj so obj/splunk.o obj/logger.o obj/config.o
	gcc -shared -o so/libsplunk.so obj/splunk.o obj/logger.o obj/config.o

tests: src/test_main.h src/test_main.c src/logger.h src/logger_test.c obj/config.o obj/splunk.o
	gcc -o tests src/test_main.c src/logger_test.c obj/config.o obj/splunk.o

.PHONY: test
test: tests
	./tests

.PHONY: dist
dist:
	@mkdir -p dist
	docker buildx build --platform linux/$(ARCH) -o type=image,name=libsplunk-builder:$(ARCH),push=false .
	docker rm -f libsplunk-builder 2>/dev/null || true
	docker run -d --platform linux/$(ARCH) --name libsplunk-builder libsplunk-builder:$(ARCH) sleep inf
	docker exec libsplunk-builder make test all
	docker cp libsplunk-builder:/libsplunk/so/libsplunk.so dist/libsplunk_$(ARCH).so
	docker rm -f libsplunk-builder

.PHONY: deb-rpm-package
%-package:
ifneq ($(SKIP_COMPILE), true)
	$(MAKE) dist
endif
	@mkdir -p dist
	docker build -t instrumentation-fpm packaging/fpm
	docker run --rm -v $(CURDIR):/instrumentation -e PACKAGE=$* -e VERSION=$(VERSION) -e ARCH=$(ARCH) instrumentation-fpm
