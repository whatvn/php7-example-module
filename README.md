# php7-example

An example on how to write php7 extension 

# BUILD


```
phpize
./configure
make
make test
make install 
```


# CONFIGURATION



php.ini

```bash
extension=example.so
```


# Usage


```php
<?php

$c = new example("Hello");

echo $c->get(), "\n";

``` 




# CREDITs:

- No credit required 


# LICENSE

As always, do whatever you want ;)
I do this to learn thing only



