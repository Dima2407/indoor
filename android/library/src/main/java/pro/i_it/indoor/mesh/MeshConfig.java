package pro.i_it.indoor.mesh;

public class MeshConfig {

    private final double nx;
    private final double ny;
    private final double dx;
    private final double dy;
    private final double x0;
    private final double y0;

    public MeshConfig(double nx, double ny, double dx, double dy, double x0, double y0) {
        this.nx = nx;
        this.ny = ny;
        this.dx = dx;
        this.dy = dy;
        this.x0 = x0;
        this.y0 = y0;
    }

    public MeshConfig(double nx, double ny, double dx, double dy) {
        this(nx, ny, dx, dy, 0, 0);
    }
}
