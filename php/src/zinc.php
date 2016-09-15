<?php
require_once __DIR__."/../vendor/autoload.php";

use Zinc\Components as ZCom;
use Zinc\Lib as ZLib;

/**
 * Global Zinc\Utils instance
 */
$utils = new ZLib\Utils;

// Test console
$utils->consoleTest();

// Create points
$point1 = new ZCom\Point([1, 2, 3]);
$point2 = new ZCom\Point([4, 5, 6]);

// Test point output
echo "Formatted point: $point1".PHP_EOL;
echo "Subtracted point: ".$point1->sub($point2).PHP_EOL;
echo "Added point: ".$point1->add($point2).PHP_EOL;
echo "Double-added point: ".$point1->add($point2)->add($point2).PHP_EOL;

// Create cubies
$cubie1 = new ZCom\Cubie("A");
$cubie2 = new ZCom\Cubie("B");
$cubie3 = new ZCom\Cubie("C");

// Create cubie vector from objects
$vector1 = new ZCom\CubieVector([$cubie1, $cubie2, $cubie3]);

// ... from strings
$vector2 = new ZCom\CubieVector(["D", "E", "F"]);
$vector3 = new ZCom\CubieVector(["G", "H", "I"]);

// Bad vector
$badVector = new ZCom\CubieVector([1,2,3]);

// Access bad vector
echo "Bad vector implode: ".implode(", ", $badVector->getArrayCopy()).PHP_EOL;

// Test array capabilities of vector
echo "Vector 1 implode: ".implode(", ", $vector1->getArrayCopy()).PHP_EOL;

// Add/change vector values
$vector1[1] = new ZCom\Cubie("X");
$vector1[] = new ZCom\Cubie("Y");

// Test array capabilities of vector
echo "Vector 1 implode after change: ".implode(", ", $vector1->getArrayCopy()).PHP_EOL;

// Create cubie matrix
$matrix = new ZCom\CubieMatrix([$vector1, $vector2, $vector3]);

// Loop through matrix
foreach ($matrix as $key => $vector) {
    echo "Vector $key foreach: ".implode(", ", $vector->getArrayCopy()).PHP_EOL;
}

// Create slice from string
$slice1 = new ZCom\Slice("ABCDEFGHI", 3);

// ... from matrix
$slice2 = new ZCom\Slice($matrix);

// Pull specific cubie from matrix and output value
echo "Matrix[1][2]: ".$matrix[1][2].PHP_EOL;

// Format slice
echo "Slice formats:".PHP_EOL;
echo $slice1->format();
echo $slice2->format();

// Slice state
echo "Slice 1 state: ".$slice1->state().PHP_EOL;
echo "Slice 2 state: ".$slice2->state().PHP_EOL;

// Rotate slice
$slice1->rotate();

// Display rotated slice
echo "After rotating slice 1 clockwise:".PHP_EOL;
echo $slice1->format();

// Rotate slice again
$slice1->rotate(ZCom\Rotation::COUNTER_CLOCKWISE);

// Display rotated slice
echo "After rotating slice 1 counter-clockwise:".PHP_EOL;
echo $slice1->format();

// Rotate slice again (half turn)
$slice1->rotate(ZCom\Rotation::HALF);

// Display rotated slice
echo "After rotating slice 1 half:".PHP_EOL;
echo $slice1->format();
?>