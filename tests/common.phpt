--TEST--
example()
--SKIPIF--
<?php if(!extension_loaded("example")) print "skip"; ?>
--FILE--
<?php
$e = new example("Hello");
echo $e->get(), "\n";
?>
--EXPECT--
Hello
