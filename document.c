/* Name: Zijie Cai UID: 117081794 Directory-ID: zai28 */
/* Project2: Document Manager */

#include <stdio.h>
#include <string.h>
#include "document.h"
           
/* This functiobn initializes *doc to have 0 paragraphs and sets the document’s 
name based on the provided parameter value. The function returns FAILURE if doc 
is NULL, name is NULL, or if the length of the name is not between 1 and 
MAX_STR_SIZE; otherwise the function returns SUCCESS */
int init_document(Document *doc, const char *name) {
    if (doc == NULL || name == NULL || strlen(name) < 1 || 
        strlen(name) > MAX_STR_SIZE) {
            return FAILURE; 
    } else {
        doc->number_of_paragraphs = 0;
        strcpy(doc->name, name);
        return SUCCESS;
    }
}

/* This function sets the number of paragraphs to 0. The function returns 
FAILURE if doc is NULL; otherwise the function returns SUCCESS */ 
int reset_document(Document *doc) {
    if (doc == NULL) {
        return FAILURE; 
    } else {
        doc->number_of_paragraphs = 0;
        return SUCCESS;
    }
}

/* This function prints the document’s name, number of paragraphs, followed by 
the paragraphs. Exactly one empty line (with zero characters before the newline) 
is inserted between every two successive paragraphs. The function returns 
FAILURE if doc is NULL; otherwise the function returns SUCCESS */
int print_document(Document *doc) {
    int i, j; 
    if (doc == NULL) {
        return FAILURE;
    } else {

        printf("Document name: \"%s\"\n", doc->name);
        printf("Number of Paragraphs: %d\n", doc->number_of_paragraphs);

        /* The nested for loop iterates through each paragraph of the document 
        and print the each corresponding line of that paragraph */
        for (i = 0; i < doc->number_of_paragraphs; ++i) {
            for (j = 0; j < doc->paragraphs[i].number_of_lines; ++j) {
                printf("%s\n", doc->paragraphs[i].lines[j]);
            }

            /* Check whether there is another paragraph in the document after
            the current one or not. If so, add an empty line before printing
            the next paragraph */
            if (i < doc->number_of_paragraphs - 1) {
                printf("\n"); 
            }
        }
        return SUCCESS;
    }
}

/* This function adds a paragraph after the specified paragraph number. 
Paragraph numbers in the document start at 1. If paragraph number is 0 the 
paragraph is added at the beginning of the document. The function returns 
FAILURE if doc is NULL, the document already has the maximum number of 
paragraphs (MAX PARAGRAPHS), or if paragraph number is negative or higher than 
the number of paragraphs in the document; otherwise, the function returns 
SUCCESS */
int add_paragraph_after(Document *doc, int paragraph_number) {
    int i; 
    if (doc == NULL || doc->number_of_paragraphs == MAX_PARAGRAPHS 
        || paragraph_number < 0 
        || paragraph_number > doc->number_of_paragraphs) {
        return FAILURE;
    } 

    /* If the original document is empty (has no paragraphs), add a new
    empty paragraph with no lines at the beginning */ 
    if (doc->number_of_paragraphs == 0) {

        /* Insert a new paragraph */
        doc->paragraphs[0].number_of_lines = 0; 

        /* Update the number of paragraphs in the document */
        doc->number_of_paragraphs += 1; 
        return SUCCESS; 
    } 

    /* If the document is not empty and the paragraph_number is equal
    to the number of paragraphs in the document, add a new empty
    paragraph with no lines at the end of the document */ 
    if (paragraph_number == doc->number_of_paragraphs) {

        /* Insert a new paragraph */
        doc->paragraphs[paragraph_number].number_of_lines = 0;

        /* Update the number of paragraphs in the document */ 
        doc->number_of_paragraphs += 1; 
        return SUCCESS; 
    } 

    /* If the document is not empty, add a new empty paragraph with no 
    lines at the corresponding index (paragraph_number) and shift the 
    original paragraphs to the right in the array by adding an extra 
    space at the end and traversing backwards */ 
    else {
        for (i = doc->number_of_paragraphs; i > paragraph_number; --i) {
            doc->paragraphs[i] = doc->paragraphs[i - 1];
        }

        /* Insert a new paragraph */
        doc->paragraphs[paragraph_number].number_of_lines = 0; 
                
        /* Update the number of paragraphs in the document */ 
        doc->number_of_paragraphs += 1;
        return SUCCESS; 
    }
}

/* This function adds a new line after the line with the specified line number. 
Line numbers start at 1. If line number is 0, the new line is added at the 
beginning of the paragraph. The function returns FAILURE if doc is NULL, 
paragraph number does not refer to an existing paragraph, the paragraph already 
has the maximum numberof lines allowed, line number is negative or higher than 
the available number oflines, or new line is NULL; otherwise, the function
returns SUCCESS */
int add_line_after(Document *doc, int paragraph_number, int line_number
		          , const char *new_line) {
    int i; 
    if (doc == NULL || paragraph_number < 0 
        || paragraph_number > doc->number_of_paragraphs 
        || doc->paragraphs[paragraph_number - 1].number_of_lines 
        == MAX_PARAGRAPH_LINES || line_number < 0 
        || line_number > doc->paragraphs[paragraph_number - 1].number_of_lines
        || new_line == NULL) {
        return FAILURE; 
    } 

    /* If the paragraph is empty (has no lines), add the new line at the 
    beginning of the paragraph */ 
    if (doc->paragraphs[paragraph_number - 1].number_of_lines == 0) {

        /* Copy the new line to the beginning of the paragraph */ 
        strcpy(doc->paragraphs[paragraph_number - 1].lines[0], new_line);

        /* Update the number of lines in the paragraph */
        doc->paragraphs[paragraph_number - 1].number_of_lines += 1; 
        return SUCCESS; 
    } 

    /* If the paragraph is not empty and the line_number is equal to the number 
    of lines in the paragraph, add the new line at the end of the paragraph */ 
    if (line_number == doc->paragraphs[paragraph_number - 1].number_of_lines) {

        /* Insert the new line */
        strcpy(doc->paragraphs[paragraph_number - 1].lines[line_number]
              , new_line);

        /* Update the number of lines in the paragraph */ 
        doc->paragraphs[paragraph_number - 1].number_of_lines += 1; 
        return SUCCESS; 
    } 

    /* If the paragraph is not empty, add the new line at the corresponding 
    index (line_number) and shift the original lines to the right in the array 
    by adding an extra space at the end and traversing backwards */ 
    else {
        for (i = doc->paragraphs[paragraph_number - 1].number_of_lines
            ; i > line_number; --i) {
            strcpy(doc->paragraphs[paragraph_number - 1].lines[i]
                  , doc->paragraphs[paragraph_number - 1].lines[i - 1]); 
        }

        /* Insert the new line */
        strcpy(doc->paragraphs[paragraph_number - 1].lines[line_number]
              , new_line); 
                
        /* Update the number of lines in the paragraph */ 
        doc->paragraphs[paragraph_number - 1].number_of_lines += 1; 
        return SUCCESS; 
    }
}

/* This function returns the number of lines in a paragraph using the number of
lines out parameter. The function returns FAILURE if doc or number of lines is 
NULL or if paragraph number does not refer to an existing paragraph; otherwise, 
the function returns SUCCESS */
int get_number_lines_paragraph(Document *doc, int paragraph_number 
                              , int *number_of_lines) {
    if (doc == NULL || number_of_lines == NULL || paragraph_number < 0 
        || paragraph_number > doc->number_of_paragraphs) {
        return FAILURE; 
    } else {
        *number_of_lines 
        = doc->paragraphs[paragraph_number - 1].number_of_lines; 
        return SUCCESS; 
    }
}

/* This function appends a new line to the specified paragraph. The conditions 
that make add line after fail apply to this function as well. The function 
returns SUCCESS if the line is appended */ 
int append_line(Document *doc, int paragraph_number, const char *new_line) {
    int boolean; 
    if (doc == NULL || paragraph_number < 0 
        || paragraph_number > doc->number_of_paragraphs 
        || doc->paragraphs[paragraph_number - 1].number_of_lines 
        == MAX_PARAGRAPH_LINES || new_line == NULL) {
        return FAILURE; 
    } else {

        /* Store the output result of the function call */
        boolean 
        = add_line_after(doc, paragraph_number
                        , doc->paragraphs[paragraph_number - 1].number_of_lines
                        , new_line); 

        /* Check whether the function call fails or not */
        if (boolean == FAILURE) {
            return FAILURE; 
        } else {
            return SUCCESS; 
        }
    }
}

/* This function removes the specified line from the paragraph. The function 
returns FAILURE if doc is NULL, paragraph number does not refer to an existing 
paragraph, or line number does not refer to an existing line; otherwise the 
function returns SUCCESS */
int remove_line(Document *doc, int paragraph_number, int line_number) {
    int i, j; 
    if (doc == NULL || paragraph_number < 0 
       || paragraph_number > doc->number_of_paragraphs || line_number <= 0
       || line_number > doc->paragraphs[paragraph_number - 1].number_of_lines) {
       return FAILURE; 
    }

    /* Remove the specified line when it is the last line in the paragraph */
    if (line_number == doc->paragraphs[paragraph_number - 1].number_of_lines) {

        /* Drop the last line by decrementing number of lines by 1 */ 
        doc->paragraphs[paragraph_number - 1].number_of_lines -= 1; 
    }

    /* Otherwise, remove the specified line and replaces it with the next line 
    by traversing from the target element until the last element and copy each 
    of the next element to the previous index. Note to copy the string over 
    character by character */
    for (i = line_number - 1
        ; i < doc->paragraphs[paragraph_number - 1].number_of_lines - 1; ++i) {
        for (j = 0; j < MAX_STR_SIZE; ++j) {
            doc->paragraphs[paragraph_number - 1].lines[i][j] 
            = doc->paragraphs[paragraph_number - 1].lines[i + 1][j]; 
        } 
    }

    /* Update the number of lines after removal */ 
    doc->paragraphs[paragraph_number - 1].number_of_lines -= 1;
    return SUCCESS;
}


/* This function adds the first data lines number of rows from the data array to 
the document, starting a new paragraph at the beginning of the document. A row 
with an empty string starts a new paragraph. So if there are n empty rows in the 
first data lines, the function adds n + 1 new paragraphs to the document. The 
function returns FAILURE if doc is NULL, data is NULL or data lines is 0. 
It also returns FAILURE if adding data lines number of rows would violate the 
max number of allowed paragraphs or the max number of lines in a paragraph; in 
this case, either leave the document unchanged or grow the document to the 
maximum allowed. In all other cases, the function returns SUCCESS */
int load_document(Document *doc, char data[][MAX_STR_SIZE + 1]
                 , int data_lines) {
    int i, boolean, counter = 0; 
    if (doc == NULL || data == NULL || data_lines == 0) {
        return FAILURE; 
    } 

    /* Initialize a new paragraph at the beginning of the document */ 
    add_paragraph_after(doc, 0);

    /* Update the counter to track the new paragraph number */
    counter += 1;

    /* Loop through the loaded document and append each line to the paragraph, 
    if the line is an empty string, initialize a new paragraph */
    for (i = 0; i < data_lines; ++i) {
        if (!strcmp(data[i], "")) {

            /* Store the output result of function call and add a new paragraph
            after the current paragraph */ 
            boolean = add_paragraph_after(doc, counter);
            
            /* Check whether the function call fails or not */
            if (boolean == FAILURE) {
                return FAILURE;
            }

            /* Update the counter to track the new paragraph number */
            counter += 1;
        } else {

            /* Store the output result of function call and append the line to 
            the current paragraph */ 
            boolean = append_line(doc, counter, data[i]); 

            /* Check whether the function call fails or not */
            if (boolean == FAILURE) {
                return FAILURE;
            }
        }
    }
    return SUCCESS; 
}

/* This function eplaces every appearance of the text target in the document 
with the text replacement. The function returns FAILURE if doc, target or 
replacement is NULL; otherwise the function returns SUCCESS */ 
int replace_text(Document *doc, const char *target, const char *replacement) {
    int i, j; 
    if (doc == NULL || target == NULL || replacement == NULL) {
        return FAILURE; 
    } 

    /* Loop through each line in the document */
    for (i = 0; i < doc->number_of_paragraphs; ++i) {
        for (j = 0; j < doc->paragraphs[i].number_of_lines; ++j) {

            /* Call helper function to replace text in each line */
            replace_in_line(doc, target, replacement, i, j); 
        }
    }
    return SUCCESS; 
}

int replace_in_line (Document *doc, const char *target, const char *replacement
                    , int paragraph_index, int line_index) {
    int i = 0, replacement_length = strlen(replacement);
    char *target_element, *target_line; 
    char replacement_copy[MAX_STR_SIZE + 1] = "";
    int replacement_copy_length; 

    /* Pointer to the target line in the document being replaced */ 
    target_line = doc->paragraphs[paragraph_index].lines[line_index]; 

    /* Pointer to the first occurrence to the target element in the sequqence or 
    a null pointer if the target is not present in the sequence */ 
    target_element = strstr(target_line, target); 
    
    /* Traverse through the target line. If the pointer in the target line 
    points at the same address of the target element, copy the adress of 
    replacement into the replacement copy string. Then, increment the index of 
    the replacement to the index after the replacement word and update the 
    pointer to point the target line at the index after the target word. Also, 
    update the target element to point to the next target in the line if any. 
    Otherwise, copy each of the characters from the target line into the 
    replacement copy string and increment each position index by 1 */
    while (*target_line) {
        if (target_line == target_element) {
            strcpy(&replacement_copy[i], replacement);
            i += replacement_length;
            target_line += strlen(target); 
            target_element = strstr(target_element + strlen(target), target);
        } else {
            strcpy(&replacement_copy[i], target_line);
            i += 1, target_line += 1; 
        }
    }

    /* Set the last element in the character array to NULL terminator */
    replacement_copy[i] = '\0';

    /* Initialize the variable with the length of the replacement copy */
    replacement_copy_length = strlen(replacement_copy); 

    /* Loops through the replacement copy string and copy each of the characters 
    into the specified line in the document */
    for (i = 0; i < replacement_copy_length; ++i) {
        doc->paragraphs[paragraph_index].lines[line_index][i] 
        = replacement_copy[i];
    }

    /* Set the last element in the character array to NULL terminator */
    doc->paragraphs[paragraph_index].lines[line_index][i] = '\0';
    return SUCCESS;
}

/* This function highlights every appearance of the text target in the document, 
by surrounding the text with the strings HIGHLIGHT START STR and HIGHLIGHT END 
STR (see document.h). The function returns FAILURE if doc or target is NULL; 
otherwise the function returns SUCCESS */ 
int highlight_text(Document *doc, const char *target) {
    char temp[MAX_STR_SIZE + 1] = "";
    if (doc == NULL || target == NULL) {
        return FAILURE; 
    } else {

        /* Store a copy of the formatted highlighted text */
        strcat(temp, HIGHLIGHT_START_STR);
        strcat(temp, target);
        strcat(temp, HIGHLIGHT_END_STR);
        temp[strlen(target) + 2] = '\0';

        /* Replace each of the target in the document with the formatted 
        hightlighted text */
        replace_text(doc, target, temp);
        return SUCCESS; 
    }
}

/* This function removes every appearance of the text target in the document. 
The function returns FAILURE if doc or target is NULL; otherwise the function 
returns SUCCESS */ 
int remove_text(Document *doc, const char *target) {
    if (doc == NULL || target == NULL) {
        return FAILURE; 
    } else {

        /* Remove the text target by replacing it with an empty string */ 
        replace_text(doc, target, "");
        return SUCCESS;
    }
}