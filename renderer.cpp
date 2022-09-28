void render_background() {
	unsigned int* pixel = reinterpret_cast<unsigned int*>(render_state.memory);
	for (int y{}; y < render_state.height; y++) {
		for (int x{}; x < render_state.width; x++) {
			*pixel++ = 0xff52ff * x + 0x62ff27 * y;
		}
	}
}