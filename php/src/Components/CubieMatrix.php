<?php
namespace Zinc\Components;

// Array of CubieVector objects, accessible as an array
class CubieMatrix extends \ArrayObject {
    public function __construct($input = [], $flags = 0, $iterator_class = "ArrayIterator") {
        // Type check contents of array
        if ($input && !($input[0] instanceof CubieVector)) {
            // Determine type
            $type = gettype($input[0]);
            if ($type === "object") $type = get_class($input[0]);
            
            // Trigger a notice
            trigger_error("Elements must be CubieVector objects, $type found");
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