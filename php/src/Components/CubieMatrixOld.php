<?php
namespace Zinc\Components;

// Array of CubieVector objects, accessible as an array
// Should be re-implemented as an ArrayObject
class CubieMatrixOld implements \ArrayAccess, \Iterator {
    // Storage for position
    private $position = 0;
    
    // Storage for data
    private $container;
    
    public function __construct(array $vectors = []) {
        // Type check contents of array
        if ($vectors && !($vectors[0] instanceof CubieVector)) {
            // Determine type
            $type = gettype($vectors[0]);
            if ($type === "object") $type = get_class($vectors[0]);
            
            trigger_error("Elements must be CubieVector objects, $type found");
        }
        
        // Set data
        $this->position = 0;
        $this->container = $vectors;
    }
    
    public function get() {
        return $this->container;
    }
    
    /**
     * ArrayAccess methods
     */
    
    public function offsetSet($offset, $value) {
        if (is_null($offset)) {
            $this->container[] = $value;
        } else {
            $this->container[$offset] = $value;
        }
    }
    
    public function offsetExists($offset) {
        return isset($this->container[$offset]);
    }
    
    public function offsetUnset($offset) {
        unset($this->container[$offset]);
    }
    
    public function offsetGet($offset) {
        return $this->offsetExists($offset) ? $this->container[$offset] : null;
    }
    
    /**
     * Iterator methods
     */
    
    public function rewind() {
        $this->position = 0;
    }
    
    public function current() {
        return $this->container[$this->position];
    }
    
    public function key() {
        return $this->position;
    }
    
    public function next() {
        ++$this->position;
    }
    
    public function valid() {
        return isset($this->container[$this->position]);
    }
}
?>