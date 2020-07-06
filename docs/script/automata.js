function update_automaton(name) {
	var user_bound = document.getElementById(name + "_user_bound").value;
	var max_word_length = document.getElementById(name + "_max_word_length").value;
	var zoom = document.getElementById(name + "_zoom").value;
	var path = "automata/" + name + "-" + user_bound + "-" + max_word_length;
	var svg_path = path + ".svg";
	var png_path = path + ".png";
	var original_size = 1300;
	document.getElementById(name + "_zoom_lexical").innerHTML = zoom;
	var width = original_size * (zoom.substring(0, zoom.length - 1) / 100);
	var image_element = document.getElementById(name);
	image_element.onerror = "this.src='" + png_path + "'";
	image_element.src = svg_path;
	image_element.style.width = width + "em";
	document.getElementById(name + "_user_bound_lexical").innerHTML = user_bound;
	document.getElementById(name + "_max_word_length_lexical").innerHTML = max_word_length;
}

function update_bubble_sort_linux_false() {
	update_automaton("_bubble_sort_linux_false");
}

function update_ifstofunctions_defroster_min() {
	update_automaton("_ifstofunctions_defroster_min");
}

function update_merge_sort_false() {
	update_automaton("_merge_sort_false");
}

function update_sll_to_dll_rev_false() {
	update_automaton("_sll_to_dll_rev_false");
}

function update_tcas_auto_instrumented() {
	update_automaton("_tcas_auto_instrumented");
}

function update_tree_false() {
	update_automaton("_tree_false");
}

function update_schedule() {
	update_automaton("_schedule");
}

function update_DockingApproachExample_Ext() {
	update_automaton("_DockingApproachExample_Ext");
}
