extern int fuzz_sign_then_verify(const unsigned char *data,
                                 unsigned long long size);

#if defined(__cplusplus)
#define EXTERN extern "C"
#else
#define EXTERN
#endif

EXTERN int LLVMFuzzerTestOneInput(const unsigned char *data,
                                      unsigned long size) {
  return fuzz_sign_then_verify(data, size);
}
