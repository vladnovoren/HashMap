#include "list_dump.h"


void PutList(List* list, FILE* log, size_t phys_id, const int node_type) {
    assert(list);

    size_t cur_logic_id = 0;
    while (phys_id != LIST_INVALID_ID) {
        fprintf(log, "\t\t\t%zu [label = <\n", phys_id);
        fprintf(log, "\t\t\t\t<table border = \"1\" bgcolor = \"%s\">\n", node_type == FREE ? "white" : "yellow");
        fprintf(log, "\t\t\t\t\t<tr><td>%s</td></tr>\n", node_type == FREE ? "free" : "used");
        if (node_type == USED)
            fprintf(log, "\t\t\t\t\t<tr><td>value: %d</td></tr>\n", list->elems[phys_id].data);
        if (node_type == USED)
            fprintf(log, "\t\t\t\t\t<tr><td>logic_id: %zu</td></tr>\n", cur_logic_id++);
        
        fprintf(log, "\t\t\t\t\t<tr><td>prev_phys_id: ");
        if (list->elems[phys_id].prev_phys_id == LIST_INVALID_ID)
            fprintf(log, " inv");
        else
            fprintf(log, "%zu", list->elems[phys_id].prev_phys_id);
        fprintf(log, "</td></tr>\n");

        fprintf(log, "\t\t\t\t\t<tr><td>next_phys_id: ");
        if (list->elems[phys_id].next_phys_id == LIST_INVALID_ID)
            fprintf(log, " inv");
        else
            fprintf(log, "%zu", list->elems[phys_id].next_phys_id);
        fprintf(log, "</td></tr>\n");

        fprintf(log, "\t\t\t\t\t<tr><td>phys_id: %zu</td></tr>\n", phys_id);
        fprintf(log, "\t\t\t\t</table>\n");
        fprintf(log, "\t\t\t>];\n");
        phys_id = list->elems[phys_id].next_phys_id;
    }
}


void List_Dump(List* list, FILE* log) {
    assert(list);
    assert(log);

    fprintf(log, "digraph List {\n");
    fprintf(log, "\tnode [shape = plaintext];\n");
    fprintf(log, "\tedge [minlen = 3];\n");
    fprintf(log, "\tsplines = ortho;\n\n");
    fprintf(log, "\tsubgraph Stat {\n");
    fprintf(log, "\t\tstat [label = <\n");
    fprintf(log, "\t\t\t<table border = \"1\">\n");
    fprintf(log, "\t\t\t\t<tr><td>n_elems: %zu</td></tr>\n", list->n_elems);
    fprintf(log, "\t\t\t\t<tr><td>capacity: %zu</td></tr>\n", list->capacity);
    fprintf(log, "\t\t\t</table>\n");
    fprintf(log, "\t\t\t>];\n");
    fprintf(log, "\t}\n\n");

    fprintf(log, "\tsubgraph cluster_memory {\n");
    fprintf(log, "\t\tlabel = \"Nodes\";\n\n");
    fprintf(log, "\t\t{rank = same");
    for (size_t id = 0; id < list->capacity; ++id) {
        fprintf(log, "; %zu", id);
    }
    fprintf(log, "};\n");
    fprintf(log, "\t\t{rank = same");
    if (list->n_elems)
        fprintf(log, "; head; tail");
    if (list->capacity - list->n_elems)
        fprintf(log, "; free");
    fprintf(log, "};\n\n");

    fprintf(log, "\t\tsubgraph nodes {\n");

    if (list->n_elems) {
        PutList(list, log, list->head_phys_id, USED);
    }
    if (list->capacity - list->n_elems)
        PutList(list, log, list->free_phys_id, FREE);

    fprintf(log, "\n");
    fprintf(log, "\t\t\tedge [constraint = true, style = invis];\n\n");

    for (size_t id = 0; id < list->capacity - 1; ++id)
        fprintf(log, "\t\t\t%zu -> %zu;\n", id, id + 1);
    fprintf(log, "\n");

    fprintf(log, "\t\t\tedge [constraint = false, style = \"\", color = red];\n\n");
    size_t cur_phys_id = list->head_phys_id;
    while (cur_phys_id != LIST_INVALID_ID && list->elems[cur_phys_id].next_phys_id != LIST_INVALID_ID) {
        fprintf(log, "\t\t\t%zu -> %zu;\n", cur_phys_id, list->elems[cur_phys_id].next_phys_id);
        cur_phys_id = list->elems[cur_phys_id].next_phys_id;
    }
    fprintf(log, "\n");

    cur_phys_id = list->free_phys_id;
    fprintf(log, "\t\t\tedge [color = black];\n\n");
    while (cur_phys_id != LIST_INVALID_ID && list->elems[cur_phys_id].next_phys_id != LIST_INVALID_ID) {
        fprintf(log, "\t\t\t%zu -> %zu;\n", cur_phys_id, list->elems[cur_phys_id].next_phys_id);
        cur_phys_id = list->elems[cur_phys_id].next_phys_id;
    }
    fprintf(log, "\n");

    fprintf(log, "\t\t}\n\n");


    fprintf(log, "\t\tedge [dir = back, headlabel = \"\", taillabel = \"\", minlen = \"\"];\n\n");
    
    fprintf(log, "\t\tsubgraph extreme_elements {\n");
    if (list->capacity - list->n_elems){
        fprintf(log, "\t\t\tfree[label = <\n");
        fprintf(log, "\t\t\t\t<table>\n");
        fprintf(log, "\t\t\t\t\t<tr><td>free</td></tr>\n");
        fprintf(log, "\t\t\t\t</table>\n");
        fprintf(log, "\t\t\t>];\n\n");

        fprintf(log, "\t\t\t%zu -> free;\n", list->free_phys_id);
    }

    if (list->n_elems) {
        fprintf(log, "\t\t\thead [label = <\n");
        fprintf(log, "\t\t\t\t<table>\n");
        fprintf(log, "\t\t\t\t\t<tr><td>head</td></tr>\n");
        fprintf(log, "\t\t\t\t</table>\n");
        fprintf(log, "\t\t\t>];\n\n");

        fprintf(log, "\t\t\ttail [label = <\n");
        fprintf(log, "\t\t\t\t<table>\n");
        fprintf(log, "\t\t\t\t\t<tr><td>tail</td></tr>\n");
        fprintf(log, "\t\t\t\t</table>\n");
        fprintf(log, "\t\t\t>];\n");

        fprintf(log, "\t\t\t%zu -> head;\n", list->head_phys_id);
        fprintf(log, "\t\t\t%zu -> tail;\n\n", list->tail_phys_id);
    }
    fprintf(log, "\t\t}\n");
    fprintf(log, "\t}\n}\n");
}