```

deqdip
=======

Name:
        deqdip -
	 
        Implements the deqdip dequeue cache protocol for x86_64 Linux
	and provides a user mode API for Elixir, Erlang and C.

Author:
        marcel@aexa.uk
	 
Purpose:
	Elixir/Erlang is generating interest for its core friendly
	thread scheduling. This inevitably leads to an interest in
	performance characterisation.

	as such it provides confidence in establishing a baseline that
	is consistently deterministic which is key for anyone involved
	in any comparitive performance characterisation work.
	
	Read the short paper on deqdip before using it.

Requirements:

        Elevated privilege (suid) for kernel mode code execution.

Install:
        make all      - build sources
        make sign     - self sign kernel module
	make install  - install

	make clean    - preserve source files and remove all binary files
	 
        for Elixir/Erlang use copy
         api_deqdip.ex
         nif_deqdip.so
	   
	 To your project root.
	 If you prefer to have the nif in ./priv change the loadpath in the api file.

         postinstallation validation:

         iex> c("./api_deqdip")
	 [Deqdipctl]
	 iex> Elixir.Deqdipctl.deqdipctl()
	 0
	 iex>

         deqdipctl() will return 0 on success and -1 on failure this is only
	 used for testing. The formal API is deqdip_proto().
	 
	 A failure -1 probably indicates there was a problem accessing the
	 device file /sys/kernel/debug/deqdip/deqdipreq which may additionally
	 involve some problem setting root privelege or problems loading
	 the kernel module km_deqdip.ko

         A /usr/bin/deqdipctl compiled from the same 'C' source file may
	 help you further in tracing any problems.

	 Nb. deqdipctl() is only a primitive. The formal interface to
	 deqdip is via deqdip_proto().

Description:

         This package creates a kernel-module (.ko), a kernel device file,
	 a shared-library (.so) with the Erlang Virtual Machine (called a NIF)
	 an Elixir API  (.ex) and the Deqdip Decache Protocol.
	 
	 It is assumed you will be using Elixir's :timer or similar to produce
	 performance metrics.


```

