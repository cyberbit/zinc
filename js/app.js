var ALPHABET = 'ABCDEFGHIJKLM/NOPQRSTUVWXYZ';
var SEED = 'A';

$(function() {
    /*var ALPHABET_MATRIX = [
        [
            ['A', 'B', 'C'],
            ['D', 'E', 'F'],
            ['G', 'H', 'I']
        ],
        [
            ['J', 'K', 'L'],
            ['M', '/', 'N'],
            ['O', 'P', 'Q']
        ],
        [
            ['R', 'S', 'T'],
            ['U', 'V', 'W'],
            ['X', 'Y', 'Z']
        ]
    ];
    
    var DIRECTION_MASK = [
        [-1, -1], []
    ];*/
    
    console.log("alphabet: %o", ALPHABET);
    //console.log("alphabet matrix: %o", ALPHABET_MATRIX);
    
    // Debug alphabet index
    /*$.each(ALPHABET.split(''), function(i, v) {
        console.log("index of %o: %o", v, JSON.stringify(reduceIndex(alphabetToIndex(ALPHABET, v))));
    });*/
    
    //// Debug reduction
    //var reduction = stringToReduction(ALPHABET, "HEMPF");
    //console.log("HEMPF reduces to %o", reduction);
    //
    //// Debug reduction translation
    //var translation = reductionToTranslation(reduction);
    //console.log("...which translates to %o", translation);
    
    // Define test string
    var rawString = "HEMPF";
    
    // Debug string index
    var stringIndex = stringToStringIndex(ALPHABET, rawString);
    console.log("%o indexes to %o", rawString, stringIndex);
    
    // Debug string index translation
    var translation = stringIndexToTranslation(stringIndex);
    console.log("...which translates to %o", translation);
    
    // Debug follow
    var follow = followTranslation(translateIndex(alphabetToIndex(ALPHABET, SEED)), translation);
    console.log("...which follows to %o", follow);
    
    // Debug untranslation
    var untranslation = translationToStringIndex(follow);
    console.log("...which untranslates to %o", untranslation);
    
    // Debug encoded string
    var encodedString = stringIndexToString(ALPHABET, untranslation);
    console.log("...which encodes to %o", encodedString);
});

function encode(string, alphabet, seed) {
    alphabet = alphabet || ALPHABET;
    seed = seed || SEED;
    
    var sindex = stringToStringIndex(alphabet, string);
    console.debug("encode.sindex = %o", sindex);
    
    var trans = stringIndexToTranslation(sindex);
    console.debug("encode.trans = %o", trans);
    
    var follow = followTranslation(translateIndex(alphabetToIndex(alphabet, seed)), trans);
    console.debug("encode.follow = %o", follow);
    
    var untrans = translationToStringIndex(follow);
    console.debug("encode.untrans = %o", untrans);
    
    return stringIndexToString(alphabet, untrans);
}

function decode(string, alphabet, seed) {
    alphabet = alphabet || ALPHABET;
    seed = seed || SEED;
    
    var sindex = stringToStringIndex(alphabet, string);
    console.debug("decode.sindex = %o", sindex);
    
    var trans = stringIndexToTranslation(sindex);
    console.debug("decode.trans = %o", trans);
    
    var unfollow = unfollowTranslation(translateIndex(alphabetToIndex(alphabet, seed)), trans);
    console.debug("decode.unfollow = %o", unfollow);
    
    var untrans = translationToStringIndex(unfollow);
    console.debug("decode.untrans = %o", untrans);
    
    return stringIndexToString(alphabet, untrans);
}

function alphabetToIndex(alphabet, value) {
    /**
     * Decoding cheat sheet (slice-row-column = z-y-x)
     *
     * Index 0-8:                               0-y-x
     * Index 9-17:                              1-y-x
     * Index 18-26:                             2-y-x
     *
     * Index 0-2, 9-11, 18-20:                  z-0-x
     * Index 3-5, 12-14, 21-23:                 z-1-x
     * Index 6-8, 15-17, 24-26:                 z-2-x
     *
     * Index 0, 3, 6, 9, 12, 15, 18, 21, 24:    z-y-0
     * Index 1, 4, 7, 10, 13, 16, 19, 22, 25:   z-y-1
     * Index 2, 5, 8, 11, 14, 17, 20, 23, 26:   z-y-2
     */
    
    if (alphabet.length != 27) {
        console.error("Incorrect alphabet length: %o", alphabet.length);
        return false;
    }
    
    var i = alphabet.indexOf(value);
    
    // Unknown character
    if (i == -1) {
        console.error("Unknown character: %o", value);
        return false;
    }
    
    var z = parseInt(i / 9);
    var y = parseInt(i / 3) % 3;
    var x = i % 3;
    
    return [z, y, x];
}

function stringToStringIndex(alphabet, string) {
    return string.split('').map(function(v) {
        return alphabetToIndex(alphabet, v);
    });
}

function reduceIndex(index) {
    return [index[0] + 1, index[1]*3 + index[2] + 1];
}

function stringToReduction(alphabet, string) {
    return string.split('').map(function(v) {
        return reduceIndex(alphabetToIndex(alphabet, v));
    });
}

function translateIndex(index) {
    return index.map((v) => v - 1);
}

function stringIndexToTranslation(sindex) {
    return sindex.map((v) => translateIndex(v));
}

function translateReducedIndex(rindex) {
    var xy = rindex[1] - 1;
    
    var y = parseInt(xy / 3) % 3;
    var x = xy % 3;
    
    return [y - 1, x - 1];
}

function reductionToTranslation(reduction) {
    return reduction.map(function(v) {
        return translateReducedIndex(v);
    });
}

function followTranslatedIndex(index, tindex) {
    var findex = index.map(function(v, i) {
        var j = v + tindex[i];
        
        // Wrap translated index if needed
        if (j === -2) j = 1;
        else if (j === 2) j = -1;
        
        return j;
    });
    
    //console.debug('followTranslatedIndex(%o, %o) = %o', JSON.stringify(index), JSON.stringify(tindex), JSON.stringify(findex));
    
    return findex;
}

function followTranslation(startIndex, translation) {
    var previous = startIndex;
    
    return translation.map(function(v) {
        var next = followTranslatedIndex(previous, v);
        
        previous = next;
        
        return next;
    });
}

function unfollowTranslatedIndex(index, tindex) {
    var ufindex = index.map(function(v, i) {
        var j = tindex[i] - v;
        
        // Wrap translated index if needed
        if (j === -2) j = 1;
        else if (j === 2) j = -1;
        
        return j;
    });
    
    return ufindex;
}

function unfollowTranslation(startIndex, translation) {
    var previous = startIndex;
    
    return translation.map(function(v) {
        var next = unfollowTranslatedIndex(previous, v);
        
        previous = v;
        
        return next;
    });
}

function untranslateIndex(tindex) {
    return tindex.map((v) => v + 1);
}

function translationToStringIndex(translation) {
    return translation.map((v) => untranslateIndex(v));
}

function indexToAlphabet(alphabet, index) {
    /**
     * Decoding cheat sheet (slice-row-column = z-y-x)
     *
     * Index 0-8:                               0-y-x
     * Index 9-17:                              1-y-x
     * Index 18-26:                             2-y-x
     *
     * Index 0-2, 9-11, 18-20:                  z-0-x
     * Index 3-5, 12-14, 21-23:                 z-1-x
     * Index 6-8, 15-17, 24-26:                 z-2-x
     *
     * Index 0, 3, 6, 9, 12, 15, 18, 21, 24:    z-y-0
     * Index 1, 4, 7, 10, 13, 16, 19, 22, 25:   z-y-1
     * Index 2, 5, 8, 11, 14, 17, 20, 23, 26:   z-y-2
     */
    
    if (alphabet.length != 27) {
        console.error("Incorrect alphabet length: %o", alphabet.length);
        return false;
    }
    
    var i = index[0]*9 + index[1]*3 + index[2];
    
    return alphabet.substr(i, 1);
}

function stringIndexToString(alphabet, sindex) {
    return sindex.map(function(v) {
        return indexToAlphabet(alphabet, v);
    }).join('');
}