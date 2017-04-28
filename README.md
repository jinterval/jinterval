[![Build Status](https://travis-ci.org/jinterval/jinterval.svg?branch=master)](https://travis-ci.org/jinterval/jinterval)

## Build instruction:

1) Check that JDK8 is installed and JAVA_HOME environment variable is properly set.

2) Install maven3 from
http://maven.apache.org/download.html

After that, type in command-line (or in Cygwin prompt window)
from the directory that contains this file (let it be `$JINTERVAL`)

`cd $JINTERVAL`

`mvn clean install`

Find file `$JINTERVAL/p1788-launcher-java/target/p1788-launcher-java-0.1-SNAPSHOT-jar-with-dependencies.jar`

## Run instruction (Linux).

0) Create working diredctory if necessary

    `mkdir $WRK`
    
    `cd $WRK`

1) Prepare `.so` file with adapter of interval library under test.
#### Boost
`cp $JINTERVAL/p1788-launcher-java/src/main/resources/net/java/jinterval/p1788/testBoost.cpp .`

`g++ -shared -m64 -fpermissive -frounding-math -fPIC -O2 -o libtestBoost.so testBoost.cpp`

#### Filib
`cp $JINTERVAL/p1788-launcher-java/src/main/resources/net/java/jinterval/p1788/testFilib.cpp .`

`g++ -shared -m64 -frounding-math -fPIC -O2 -I$FILIBDIR/include -L$FILIBDIR/lib -lprim -o libtestFilib.so testFilib.cpp`

#### LibMoore
`cp $JINTERVAL/p1788-launcher-java/src/main/resources/net/java/jinterval/p1788/testLibMoore.cpp .`

`g++-6 -std=c++1z -shared -m64 -pipe -fconcepts -frounding-math -mfpmath=sse -msse2 -fsignaling-nans -Wall -W -fPIC -I$LIBMOOREDIR/include -o libtestmoore.so testLibMoore.cpp -Wl,--whole-archive  $LIBMOOREDIR/lib/libmoore.a -Wl,--no-whole-archive`

3) Copy test files to the working directory

`cp $JINTERVAL/p1788-launcher-java/src/main/resources/net/java/jinterval/p1788/dat/testDemo.dat .`

4) Run tests
#### Boost
`java -jar $JINTERVAL/p1788-launcher-java/target/p1788-launcher-java-0.1-SNAPSHOT-jar-with-dependencies.jar -l./libtestBoost.so -ptest_boost_ -rnan -b *.dat`

The expected output is:

```
# testDemo.dat
* atan2
Library has no Operation "atan2" in line 1 : * atan2
* sqr
* div
* sqrt
* pown
[0,0] | 0
!!0  CONTAINMENT FAILURE !!! i= []_trv ti=[1,1]_com
* sign
Library has no Operation "sign" in line 13 : * sign
* sin
[0,0]
!!0  NOT ACCURATE ! i= [-0x1.91a62633145cp-50,0x1.dcb3b399d747fp-51]_com ti=[0,0]_com ai=[-0x1p-1073,0x1p-1073]_com
[0,0x1p-1074]
!!0  NOT ACCURATE ! i= [-0x1.91a62633145cp-50,0x1.ee59d9cceba4p-50]_com ti=[0,0x1p-1074]_com ai=[-0x1p-1073,0x1.8p-1073]_com
[-0x1p-1070,0]
!!0  NOT ACCURATE ! i= [-0x1.91a62633145cp-50,0x1.dcb3b399d747fp-51]_com ti=[-0x1p-1070,0]_com ai=[-0x1.2p-1070,0x1p-1073]_com
[-0x1p-1074,0x1p-1074]
!!0  NOT ACCURATE ! i= [-0x1.91a62633145cp-50,0x1.ee59d9cceba4p-50]_com ti=[-0x1p-1074,0x1p-1074]_com ai=[-0x1.8p-1073,0x1.8p-1073]_com
[0x1.6c6cbc45dc8dep6,0x1.6c6cbc45dc8dep6]
!!0  NOT ACCURATE ! i= [-0x1.3dcb3b399d748p-47,0x1.611a62633145cp-46]_com ti=[-0x1.6d61b58c99c43p-60,-0x1.6d61b58c99c42p-60]_com ai=[-0x1.0005b586d6328p-46,0x1.fff494f2539b5p-47]_com
* tan
```

#### Filib
`java -jar $JINTERVAL/p1788-launcher-java/target/p1788-launcher-java-0.1-SNAPSHOT-jar-with-dependencies.jar -l$FILIBDIR/lib/libprim.so -l./libtestFilin.so -ptest_filib_ -rnan -b *.dat`

The expected output is:

```
* atan2
Library has no Operation "atan2" in line 1 : * atan2
* sqr
* div
* sqrt
* pown
* sign
Library has no Operation "sign" in line 13 : * sign
* sin
* tan
```

or check if Filib returns tightest intervals

`java -jar $JINTERVAL/p1788-launcher-java/target/p1788-launcher-java-0.1-SNAPSHOT-jar-with-dependencies.jar -l$FILIBDIR/lib/libprim.so -l./libtestFilin.so -ptest_filib_ -rnan -b -t *.dat`

The expected output is:

```
* atan2
Library has no Operation "atan2" in line 1 : * atan2
* sqr
* div
[1,2] | [0,0]
!!0  NOT TIGHT ! i= [0x1.fffffffffffffp1023,Infinity]_dac ti=[]_trv ai=[-Infinity,Infinity]_trv
* sqrt
[-Infinity,Infinity]
!!0  NOT TIGHT ! i= [-0x1p-1074,Infinity]_dac ti=[0,Infinity]_trv ai=[-0x1p-1074,Infinity]_trv
* pown
* sign
Library has no Operation "sign" in line 13 : * sign
* sin
[0x1.6c6cbc45dc8dep6,0x1.6c6cbc45dc8dep6]
!!0  NOT TIGHT ! i= [-0x1.6d61b58c99c4ep-60,-0x1.6d61b58c99c3ap-60]_com ti=[-0x1.6d61b58c99c43p-60,-0x1.6d61b58c99c42p-60]_com ai=[-0x1.0005b586d6328p-46,0x1.fff494f2539b5p-47]_com
[0x1.ce1432eac7048p1023,0x1.ce1432eac7048p1023]
!!0  NOT TIGHT ! i= [-1,1]_com ti=[0x1.195b6d2ff4c2cp-50,0x1.195b6d2ff4c2dp-50]_com ai=[-0x1.0000000000001p0,0x1.0000000000001p0]_com
* tan
[0x1.f2e22199cf3d1p578,0x1.f2e22199cf3d1p578]
!!0  NOT TIGHT ! i= [-Infinity,Infinity]_dac ti=[-134118393330558800,-134118393330558784]_com ai=[-Infinity,Infinity]_trv
```

#### LibMoore
`java -jar $JINTERVAL/p1788-launcher-java/target/p1788-launcher-java-0.1-SNAPSHOT-jar-with-dependencies.jar -lmpfr -ltestmoore -ptest_moore_ -rneg -b -t *.dat`

The expected output is:

```
# testDemo.dat
* atan2
* sqr
* div
* sqrt
* pown
* sign
* sin
```

5) Copy more test files and test them

`cp $JINTERVAL/p1788-launcher-java/src/main/resources/net/java/jinterval/p1788/dat/*.dat .`

`java -jar $JINTERVAL/p1788-launcher-java/target/p1788-launcher-java-0.1-SNAPSHOT-jar-with-dependencies.jar ......`

## Develop instruction (Netbeans)

1) Install Netbeans-8.1
2) Create directory `$JINTERVAL/wrk`. The Netbeans project will use it as `$WRK`.
4) In Netbeans open project `$JINTERVAL`
5) Clean and Build all
6) In Project tab click on `jinterval` then on `Modules` then on `p1788-launcher-java`
   Netbeans will open `the p1788-launcher-java`. Set it as main project
7) In project tab click on `p1788-launcher-java`, then on `Source packages`, then on `net.java.jinterval.launcher`, then `GccRunner.java`.
8) This file contains paths to a few interval C libraries and tries to compile adapters for them. Uncomment the desired adapter.
   Fix paths to those on your machine
9) Debug project
The expected result is `.so` files with adapters in `$JINTERVAL/wrk`.

Good luck!!!

