Assignment 1 Readme

I did all of my development on this assignment using Clion. Because I wasn't sure the requirements for the demo, I opted to use a docker config.
I am using an ARM based mac, so I used a dockerfile to create a docker image of an X86 that I can use to mimic a build.

With this, I linked the docker CMAKE to this assignment and ran the assignment using the build, run and debug functionality (simmilar to VScode)

I included the docker file if you were interested. But below are the commands used to build and run from command line.

For brevity, and because I don't know if we are allowed or not, I used a CMake and a Make file to handle this.

```
cmake ..
make
./COMP5421_Assignment1
```




