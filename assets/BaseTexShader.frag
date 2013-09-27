varying mediump vec2 textureCoordinate;
uniform sampler2D textureSampler;

void main()
{
    gl_FragColor = texture2D(textureSampler, textureCoordinate);
}