<?php
namespace Zinc\Components;

// Array of Cubie objects, accessible as an array
class CubieVector implements \ArrayAccess, \Iterator {
    // Storage for position
    private $position = 0;
    
    // Storage for data
    private $container;
    
    public function __construct(array $cubies = []) {
        // Type check contents of array
        if ($cubies && !($cubies[0] instanceof Cubie)) {
            // Determine type
            $type = gettype($cubies[0]);
            if ($type === "object") $type = get_class($cubies[0]);
            
            trigger_error("Elements must be Cubie objects, $type found");
        }
        
        // Set data
        $this->position = 0;
        $this->container = $cubies;
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