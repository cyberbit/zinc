<?php
require_once __DIR__."/../vendor/autoload.php";

use Zinc\Components as ZCom;

/**
 * Global Zinc\Utils instance
 */
$utils = new Zinc\Utils;

// Test console
$utils->consoleTest();

// Create points
$point1 = new ZCom\Point([1, 2, 3]);
$point2 = new ZCom\Point([4, 5, 6]);

// Test point output
echo "Formatted point: $point1\n";
echo "Subtracted point: ".$point1->sub($point2)."\n";
echo "Added point: ".$point1->add($point2)."\n";
echo "Double-added point: ".$point1->add($point2)->add($point2)."\n";

// Create cubies
$cubie1 = new ZCom\Cubie("A");
$cubie2 = new ZCom\Cubie("B");
$cubie3 = new ZCom\Cubie("C");

// Create cubie vector
$vector1 = new ZCom\CubieVector([$cubie1, $cubie2, $cubie3]);
$vector2 = new ZCom\CubieVector([
    new ZCom\Cubie("D"),
    new ZCom\Cubie("E"),
    new ZCom\Cubie("F")
]);
$vector3 = new ZCom\CubieVector([
    new ZCom\Cubie("G"),
    new ZCom\Cubie("H"),
    new ZCom\Cubie("I")
]);

// Test array capabilities of vector
echo "Vector 1 implode: ".implode(", ", $vector1->get())."\n";

// Add/change vector values
$vector1[1] = new ZCom\Cubie("X");
$vector1[] = new ZCom\Cubie("Y");

// Test array capabilities of vector
echo "Vector 1 implode after change: ".implode(", ", $vector1->get())."\n";

// Create cubie matrix
$matrix = new ZCom\CubieMatrix([$vector1, $vector2, $vector3]);

// Loop through matrix
foreach ($matrix as $key => $vector) {
    echo "Vector $key foreach: ".implode(", ", $vector->get())."\n";
}
?>