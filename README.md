# RC Robot Control C library

*Not recommended for third-party use*

- unstable interface
- only for proof-of-concept
- unoptimal implementation

This is just some glue code that I need temporarily.

# Overview & Notes

- UDP robot control
- command ordering

Using MLSP for simple commands has overhead of 8 bytes per packet.\
A single sequence or timestamp field should be sufficient.

This library purposefully ignores network byte order (big endian/little endian).

## Platforms 

Unix-like operating systems (e.g. Linux).

The dependency is indirectly through [MLSP](https://github.com/bmegli/minimal-latency-streaming-protocol).

Tested on Ubuntu 18.04.

## Dependencies

Library depends on:
- [MLSP](https://github.com/bmegli/minimal-latency-streaming-protocol)

Dependencies are included as submodules

## Building Instructions

Tested on Ubuntu 18.04.

``` bash
# update package repositories
sudo apt-get update 
# get compilers and make 
sudo apt-get install build-essential
# get cmake
sudo apt-get install libcurl4 cmake
# get git
sudo apt-get install git
# clone the repository with *RECURSIVE* for submodules
git clone --recursive https://github.com/bmegli/robot-control.git

# finally build the shared library
cd robot-control
mkdir build
cd build
cmake ..
make
```

## Using

```C

	struct rc *r;

	struct rc_net_config net_config = {"127.0.0.1", 9999}; //host, port

	r = rc_init(&net_config);
	
	if(!rc)
	{
		//handle error case
	}

	//... some control loop
	rc_command(r, COMMAND, ARG1, ARG2);
	//...


	rc_close(r);
```

## License

Library and my dependencies are licensed under Mozilla Public License, v. 2.0

This is similiar to LGPL but more permissive:
- you can use it as LGPL in prioprietrary software
- unlike LGPL you may compile it statically with your code

Like in LGPL, if you modify this library, you have to make your changes available.
Making a github fork of the library with your changes satisfies those requirements perfectly.

Since you are linking to FFmpeg libraries consider also `avcodec` and `avutil` licensing.
