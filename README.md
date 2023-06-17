# PHP Encryption Extension

This is a PHP encryption extension but its encrypts data and stores data in the jpg file.

## Installation

To install the extension use this commands:

```
$ git clone https://github.com/MithatGuner/crypter.git
$ cd crypter
$ phpize
$ ./configure
$ make
$ sudo make install
```

## Documentation
Edit encryption key in php_mitcrypt.h file.
```
ENCRYPTION_KEY "9876666666666666666666"
```
Put this code into php.ini file.

```
extension=mitcrypt
```
### Functions

`char* mitcrypt_encode( string $str = 'Hello World', string $file = 'test.jpg' )`

`char* mitcrypt_decode( string $file = 'test.jpg' )`

## Examples
```php
Create File That Contains PHP Code Ex:

data_to_encode.txt
    for ($i = 0; $i <= 100; $i++){
        echo $i;
    }
    
mitcrypt_encode(file_get_contents("data_to_encode.txt", "test.jpg"));
mitcrypt_decode("test.jpg"); 
```

## Example Output Image :
![alt text](example_image.jpg "Encrypted Data")

```
Data convert to binary encrypted and drawed into jpg file
Each color has meaning
Black = 1
White = 0
```