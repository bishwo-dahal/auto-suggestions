let input = "nuxt";
let words = require("./words");
let compare = (a, b) => {
    if (a.toUpperCase() === b.toUpperCase()) {
        return true;
    }
    return false;
}
let wordFound = words.indexOf(input);
if (wordFound === -1) {
    console.log("No matching words found ");
    console.log("Suggestions for you are \n");
    let suggestions, previousSuggestion;
    suggestions = words;
    suggestions = suggestions.filter(currentElem => {
        return currentElem.length === input.length;
    });
    // removes elements whose size doesnot match with input text
    for (let curr = 0; curr < input.length; curr++) {
        previousSuggestion = suggestions;
        // for saving suggestions one step before

        suggestions = suggestions.filter(currentElem => {
            return compare(currentElem.charAt(curr), input.charAt(curr));
        });
        console.log("Suggestions after filtering first level ", curr, input[curr], suggestions)
        // Here the filtering is opposite than that of c++
        // filtering words whose character matches

        if (suggestions.length === 0) {
            suggestions = previousSuggestion;
            curr++;
            console.log("Suggestions after filtering first level ", curr, input[curr], suggestions)

            if (curr < input.length) {
                suggestions = suggestions.filter(currentElem => {
                    return compare(currentElem.charAt(curr), input.charAt(curr));
                });
                console.log("Where the length < 0 ", suggestions);
                if (suggestions.length === 0) {
                    suggestions = previousSuggestion;
                    break;
                }
                previousSuggestion = suggestions;
            } else {
                break;
            }
        }
    }
    if (suggestions.length > 5) {
        previousSuggestion = suggestions;
        suggestions = suggestions.filter(currentElem => {
            return compare(input.charAt(0), currentElem.charAt(0));
        });
        if (suggestions.length === 0) {
            suggestions = previousSuggestion;
        }
        if (suggestions.length > 5) {
            suggestions = suggestions.slice(0, 5);
            // for slicing the first 5 members
        }
    }
    if (suggestions.length === 0) {
        suggestions = previousSuggestion;
    }

    console.log(suggestions);

} else {
    console.log("Your word was found \n Here are words near it");
    console.log(words[wordFound - 1], words[wordFound + 1]);
}
// It gives more importance to words at first