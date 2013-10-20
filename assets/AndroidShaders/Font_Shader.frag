precision mediump float;
varying vec2 textureCoordinate;
uniform vec4 colorMultiplier;
uniform sampler2D textureSampler;

void main()
{
    gl_FragColor = texture2D(textureSampler, textureCoordinate)*colorMultiplier;
}