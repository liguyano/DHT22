# DHT22
DHT22 driver
## update in 23/3/2023  
problem solved;  
```t1=dht_read(&t1, &t2,0);```  
correct is  
`dht_read(&t1, &t2,0);`
## base struct
the basement of this problem already build, but the wet only can 
  read data when first running. After that it return 0. 
and the reason unknown. 