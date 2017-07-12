# Utility to Convert Conductivity to Salinity

### Installation

##### Become root user
```
[akshay@localhost tmp]$ su 
Password: 
```
##### Extract compressed file
```
[root@localhost tmp]# unzip conductivity_to_salinity-master.zip
README.md
cond_to_salt/ 
cond_to_salt/Makefile 
cond_to_salt/cond_to_salt_debug.c 
cond_to_salt/README 
```

##### Go to cond_to_salt directory

```
[root@localhost tmp]# cd cond_to_salt
```

##### Compile & install

```
[root@localhost cond_to_salt]# make 
[root@localhost cond_to_salt]# make install 
```

##### Version

```
[root@localhost cond_to_salt]# cond_to_salt   --version 
Rev 1.0.0 (Thu Jun 11 16:41:38 UTC 2015) 
```

##### Help

```
[root@localhost cond_to_salt]# cond_to_salt   --help 

Usage               
                cond_to_salt [OPTIONS] 

Arguments 

                -t --temp Temperature deg C ITPS-68 
                -c --cond Conductivity S/m 
                -p --pres Pressure in decibars 
                -v --version Show program version 
                -h --help Show help 

Examples : 
	     cond_to_salt   --temp=28.8777 --cond=5.779922 --pres=2.011 
	     35.446250 

	     OR 

	     cond_to_salt   -t 28.8777 -c 5.779922 -p 2.011 
	     35.446250 

         If you find any bugs report to ahegde@nio.org / akshay.k.hegde@gmail.com 
``` 

### Usage

##### Usage with long options

```
[root@localhost cond_to_salt]# cond_to_salt   --temp=28.8777 --cond=5.779922 --pres=2.011 
35.4462490704
``` 

##### Usage with short options

```
[root@localhost cond_to_salt]# cond_to_salt   -t 28.8777 -c 5.779922 -p 2.011 
35.4462490704
```

##### Calculation using file

```
[akshay@localhost tmp]$ cat file.txt 
Pressure temp conductivity 
2.011 28.8777 5.779922 
3.017 28.8503 5.776798 
4.022 28.8455 5.776245 
5.028 28.8466 5.776429 
6.033 28.8480 5.776606 
7.039 28.8559 5.777541 
8.044 28.8492 5.776808 
9.050 28.8482 5.776750
``` 

##### Write simple bash script something like this

```
[akshay@localhost tmp]$ cat run.sh 
#!/usr/bin/env bash 
i=0 
while read pres temp cond; do 
	[ $i -eq 0 ] && salt="salinity" || salt=$(cond_to_salt --temp=$temp --cond=$cond --pres=$pres) 
	echo "$pres $temp $cond $salt" 
i=$((i+1)) 
done < file.txt
``` 

##### Execute

```
[akshay@localhost tmp]$ bash run.sh 
Pressure temp conductivity salinity 
2.011 28.8777 5.779922 35.4462490704 
3.017 28.8503 5.776798 35.4447235922 
4.022 28.8455 5.776245 35.4441737076 
5.028 28.8466 5.776429 35.4443334464 
6.033 28.8480 5.776606 35.4442197522 
7.039 28.8559 5.777541 35.4445155722 
8.044 28.8492 5.776808 35.4441302369 
9.050 28.8482 5.776750 35.4441782020
``` 


