<?php
require_once __DIR__."/../vendor/autoload.php";

/**
 * Global Zinc\Utils instance
 */
$utils = new Zinc\Utils;

// Test console
$utils->consoleTest();

// Create points
$point = new Zinc\Components\Point([1, 2, 3]);
$point2 = new Zinc\Components\Point([4, 5, 6]);

// Test point output
echo "Formatted point: $point\n";
echo "Subtracted point: ".$point->sub($point2)."\n";
echo "Added point: ".$point->add($point2)."\n";
echo "Double-added point: ".$point->add($point2)->add($point2)."\n";

// Create cubie
$cubie = new Zinc\Components\Cubie("A");

echo "Cubie value: ".$cubie->value()."\n";
?>