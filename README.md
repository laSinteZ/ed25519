[![](https://travis-ci.org/Warchant/ed25519.svg?branch=master)](https://travis-ci.org/Warchant/ed25519)
[![codecov](https://codecov.io/gh/Warchant/ed25519/branch/master/graph/badge.svg)](https://codecov.io/gh/Warchant/ed25519)

# Ed25519 digital signature algorithm


Ed25519 digital signature algorithm is described in [RFC8032](https://tools.ietf.org/html/rfc8032). 
This repository aims to provide modularized implementation of this algorithm. 

Originally Ed25519 consists of three *modules*: 
- algorithm itself
- SHA512 hash function
- random number generator, to generate keypairs

This repository offers at least two different C implementations for every module. 
Every implementation is tested and can be replaced with other at link-time.
New implementations can be added as well.

During cmake time, users are able to choose any of these implementations using cmake definitions:

- `EDIMPL`
    - `ref10` - portable C implementation. 
    - `amd64-64-24k` - optimized C++ ASM implementation, works only on Linux amd64. *Disabled by default*. To enable, use switch `-DAMD64_OPTIMIZED=ON`.
- `HASH`
    - `sha2_openssl` - enabled only if OpenSSL is found
    - `sha3_brainhub` - default
- `RANDOM`
    - `rand_openssl` - enabled only if OpenSSL is found
    - `dev_urandom` - default
    - `dev_random`
- `BUILD`
    - `STATIC`
    - `SHARED` - build ed25519 library as shared library (default)

**Example**:
We want to build shared library with amd64 implementation, SHA3 and PRNG, which reads entropy from `/dev/urandom`:

```bash
$ cmake .. -DAMD64_OPTIMIZED=ON -DEDIMPL=amd64-64-24k -DHASH=sha3_brainhub -DRANDOM=dev_urandom -DBUILD=SHARED
-- Target cppcheck enabled
-- Target gcovr enabled
-- EDIMPL=amd64-64-24k is selected (Ed25519 implementation)
-- HASH=sha3_brainhub is selected (SHA implementation)
-- RANDOM=dev_urandom is selected (RNG implementation)
-- BUILD=SHARED is selected (library build type)
-- Configuring done
-- Generating done
-- Build files have been written to: ...
```

# API

- API for Ed25519 is defined at [ed25519.h](./include/ed25519/ed25519.h)
- API for Hash is defined at [sha512.h](./include/ed25519/sha512.h)
- API for RNG is defined at [randombytes.h](./include/ed25519/randombytes.h)

# Modules

## ed25519 digital signature algorithm

### `ref10`

Portable but relatively slow C implementation, originally copied from SUPERCOP. 
Its API was redesigned to separate signature data from the *signed message* content.

### `amd64-64-24k`

Fast but non-portable C++ASM implementation, only for AMD64. To enable it, use switch `-DAMD64_OPTIMIZED=ON`
Copied from SUPERCOP. 
Its API was redesigned to separate signature data from the *signed message* content.

## SHA512 has function as a dependency of ed25519

### `sha2_openssl`

Implementation of FIPS 180-4 SHA2 512 hash function, which uses openssl underneath.

### `sha3_brainhub`

Implementation of FIPS 202 SHA3 512 hash function taken from [brainhub repository](https://github.com/brainhub/SHA3IUF).
Repository consisted of a single C file, which was adopted to be included in a project as a module.

## PRNG implementation as a dependency of ed25519

To generate keypair ed25519 needs a source of randomness (entropy). 

This repository offers 3 implementations:
- `rand_openssl` uses RAND_bytes from openssl
- `dev_urandom` reads entropy from `/dev/urandom`
- `dev_random` reads entropy from `/dev/random` (blocking call, uses busy waiting when user asks for more entropy than device can offer)

# Authors

[warchant](https://github.com/warchant)