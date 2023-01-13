void translate_object_asm(double dx, double dy, double dz, Vertex *vertices, int num_vertices) {
    __asm {
        mov edx, dz
        mov ecx, dy
        mov eax, dx
        movd xmm3, eax
        punpckldq xmm3, ecx
        movd eax, edx
        punpckldq xmm3, eax
        mov eax, vertices
        mov ecx, num_vertices
        loop_start:
            movaps xmm0, [eax]
            addps xmm0, xmm3
            movaps [eax], xmm0
            add eax, 16
            dec ecx
            jnz loop_start
    }
}
