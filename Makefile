all: libnan_injection_malloc.so libqnan_injection_malloc.so nan_test-nan nan_test-qnan

nan_test-nan: nan_test.c
	xlc -g -O0 -fpic -qflttrap=invalid:en $^ -o $@
nan_test-qnan: nan_test.c
	xlc -g -O0 -fpic -qflttrap=nanq:en $^ -o $@

libnan_injection_malloc.so: nan_injection_malloc.c
	gcc -g -O0 -fpic -shared $^ -o $@ -ldl

libqnan_injection_malloc.so: nan_injection_malloc.c
	gcc -g -O0 -fpic -shared -DUSE_QUIET_NAN $^ -o $@ -ldl

clean:
	rm -f libnan_injection_malloc.so libqnan_injection_malloc.so nan_test-nan nan_test-qnan
