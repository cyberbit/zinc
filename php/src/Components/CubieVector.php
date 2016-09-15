<?php
namespace Zinc\Components;

// Array of Cubie objects, accessible as an array
class CubieVector extends \ArrayObject {
    public function __construct($input = [], $flags = 0, $iterator_class = "ArrayIterator") {
        // Type check contents of array
        if ($input) {
            foreach ($input as $index=>&$value) {
                if (!($value instanceof Cubie) && !(is_string($value))) {
                    // Determine invalid type
                    $type = gettype($value);
                    if ($type === "object") $type = get_class($value);
                    
                    // Trigger a notice
                    trigger_error("Elements must be Cubie objects or strings, $type found at index $index");
                }
                
                // Create Cubie from string
                if (is_string($value)) {
                    $value = new Cubie($value);
                }
            }
        }
        
        // Set up object
        parent::__construct($input, $flags, $iterator_class);
    }
    
    public function __clone() {
        // Clone all stored objects
        foreach ($this as &$value) {
            $value = clone $value;
        }
    }
}
?>