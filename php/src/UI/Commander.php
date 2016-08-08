<?php
namespace Zinc\UI;

abstract class Commander {
    // Storage for prompt prefix
    private $m_prompt;
    
    // Storage for flags
    private $m_flags = array();
    
    public function __construct($prompt = "> ") {
        $this->m_prompt = $prompt;
    }
    
    // Prompt user for input
    public function prompt() {
        global $utils;
        
        return $utils->get_string($this->m_prompt, "grey");
    }
    
    // Run command loop
    public function loop() {
        $stop = false;
        
        do {
            $readStr = $this->prompt();
            
            // Blank commands are ignored
            if ($readStr == "") continue;
            
            // Break loop on "exit" command
            else if ($readStr == "exit") $stop = true;
            else {
                $this->parse($readStr);
            }
        } while (!$stop);
    }
    
    // Parse command
    abstract public function parse($cmd);
}