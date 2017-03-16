package khpi.com.demo.ui.opengl;

import java.util.ArrayList;
import java.util.List;

import static android.opengl.GLES20.GL_FRAGMENT_SHADER;
import static android.opengl.GLES20.GL_VERTEX_SHADER;
import static android.opengl.GLES20.glAttachShader;
import static android.opengl.GLES20.glBindAttribLocation;
import static android.opengl.GLES20.glCompileShader;
import static android.opengl.GLES20.glCreateProgram;
import static android.opengl.GLES20.glCreateShader;
import static android.opengl.GLES20.glLinkProgram;
import static android.opengl.GLES20.glShaderSource;

public final class Shaders {

    public static final String VERTEX_SHADER =
            "          uniform mat4 u_MVPMatrix;             \n"

                    + "attribute vec3 a_Position;            \n"
                    + "attribute vec4 a_Color;               \n"
                    + "attribute vec2 a_TexCoordinate;       \n"

                    + "varying vec4 v_Color;                 \n"
                    + "varying vec2 v_TexCoordinate;         \n"

                    + "void main()                           \n"
                    + "{                                     \n"
                    + "   v_Color = a_Color;                 \n"
                    + "   gl_Position = u_MVPMatrix          "
                    + "               * vec4(a_Position, 1.0);\n"
                    + "   v_TexCoordinate = a_TexCoordinate; \n"
                    + "}                                     \n";

    public static final String FRAGMENT_SHADER =
            "          precision mediump float;              \n"
                    + "varying vec4 v_Color;                 \n"

                    + "uniform sampler2D u_Texture;          \n"
                    + "varying vec2 v_TexCoordinate;         \n"

                    + "void main()                           \n"
                    + "{                                     \n"
                    + "   gl_FragColor = v_Color * "
                    + "texture2D(u_Texture, v_TexCoordinate);\n"
                    + "}                                     \n";

    public static final String SIMPLE_VERTEX_SHADER =
            "          uniform mat4 u_MVPMatrix;             \n"

                    + "attribute vec3 a_Position;            \n"

                    + "void main()                           \n"
                    + "{                                     \n"
                    + "   gl_Position = u_MVPMatrix          "
                    + "               * vec4(a_Position, 1.0);\n"
                    + "}                                     \n";

    public static final String SIMPLE_FRAGMENT_SHADER =
            "          precision mediump float;              \n"

                    + "uniform vec4 u_Color;                 \n"

                    + "void main()                           \n"
                    + "{                                     \n"
                    + "  gl_FragColor = u_Color;            \n"
                    + "}                                     \n";

    public static final String SIMPLE_FRAGMENT_SHADER_WITH_ATTRIBUTE =
            "          precision mediump float;              \n"

                    + "varying vec4 v_Color;                 \n"

                    + "void main()                           \n"
                    + "{                                     \n"
                    + "  gl_FragColor = v_Color;            \n"
                    + "}                                     \n";

    public static final String MESHING_VERTEX_SHADER =
            "          uniform mat4 u_MVPMatrix;             \n"

                    + "attribute vec3 a_Position;            \n"
                    + "attribute vec4 a_Color;               \n"
                    + "attribute vec2 a_TexCoordinate;       \n"

                    + "varying vec4 v_Color;                 \n"
                    + "varying vec2 v_TexCoordinate;         \n"

                    + "void main()                           \n"
                    + "{                                     \n"
                    + "   v_Color = a_Color;                 \n"
                    + "   gl_Position = u_MVPMatrix          "
                    + "               * vec4(a_Position, 1.0);\n"
                    + "   v_TexCoordinate = a_TexCoordinate; \n"
                    + "}                                     \n";

    public static final String MESHING_FRAGMENT_SHADER =
            "          precision mediump float;              \n"
                    + "varying vec4 v_Color;                 \n"
                    + "uniform sampler2D u_Texture;          \n"
                    + "varying vec2 v_TexCoordinate;         \n"

                    + "void main()                           \n"
                    + "{                                     \n"
                    + "   gl_FragColor = v_Color * "
                    + "texture2D(u_Texture, v_TexCoordinate);\n"
                    + "}                                     \n";

    public static int loadShaders(String vertexShader, String fragmentShader) {
        int vertexShaderHandle = createShader(vertexShader, GL_VERTEX_SHADER);
        int fragmentShaderHandle = createShader(fragmentShader, GL_FRAGMENT_SHADER);

        List<String> attributes = new ArrayList<>();
        String[] split = vertexShader.split("\n");

        for (String stroke : split) {
            if (stroke.contains("attribute")) {
                attributes.add(stroke);
            }
        }

        for (int i = 0; i < attributes.size(); i++) {
            String attributeStroke = attributes.get(i);

            String attributeName = attributeStroke.substring(attributeStroke.indexOf("a_")).replaceAll(";.*", "");

            attributes.remove(i);
            attributes.add(i, attributeName);
        }

        return createProgram(vertexShaderHandle, fragmentShaderHandle, attributes);
    }

    private static int createShader(String program, int shaderType) {
        int shaderHandle = glCreateShader(shaderType);

        glShaderSource(shaderHandle, program);
        glCompileShader(shaderHandle);

        return shaderHandle;
    }

    private static int createProgram(int vertexShaderHandle, int fragmentShaderHandle, final List<String> attributes) {
        int programHandle = glCreateProgram();

        glAttachShader(programHandle, vertexShaderHandle);
        glAttachShader(programHandle, fragmentShaderHandle);

        for (int i = 0; i < attributes.size(); i++) {
            String attribute = attributes.get(i);

            glBindAttribLocation(programHandle, i, attribute);
        }

        glLinkProgram(programHandle);

        return programHandle;
    }
}
