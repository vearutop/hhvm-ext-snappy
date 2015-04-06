# hhvm-ext-snappy
HHVM Snappy extension

This is a HHVM port of https://github.com/kjdev/php-ext-snappy

## Prerequisites ##

You need hhvm-dev to hphpize and build this extension

## Build ##

    hphpize
    cmake .
    make
    make install

## Configration ##

Edit /etc/hhvm/server.ini and add settings with path extension was installed 

    hhvm.dynamic_extension_path = /usr/local/lib64/hhvm/extensions/20150212
    hhvm.dynamic_extensions[snappy] = snappy.so
    
Restart hhvm server (as root)

    service hhvm restart

or

    invoke-rc.d hhvm restart

## Function : snappy_compress ##

string snappy_compress( string $data )

### parameters ###

data:

    The data to compress.

### return values ###

The compressed string or FALSE if an error occurred.

## Function : snappy_uncompress ##

string snappy_uncompress( string $data )

### parameters ###

data:

    The data compressed by snappy_compress(). 

### return values ###

The original uncompressed data or FALSE on error.

## Example ##

    $compressed = snappy_compress('Compress me');

    $uncompressed = snappy_uncompress($compressed);

    echo $uncompressed;