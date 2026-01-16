/****************************************************************************
 * ==> DWF_Shader_Collection_OpenGL ----------------------------------------*
 ****************************************************************************
 * Description: OpenGL ready-to-use shader collection                       *
 * Developer:   Jean-Milost Reymond                                         *
 ****************************************************************************
 * MIT License - DwarfStar Game Engine                                      *
 *                                                                          *
 * Permission is hereby granted, free of charge, to any person obtaining a  *
 * copy of this software and associated documentation files (the            *
 * "Software"), to deal in the Software without restriction, including      *
 * without limitation the rights to use, copy, modify, merge, publish,      *
 * distribute, sub-license, and/or sell copies of the Software, and to      *
 * permit persons to whom the Software is furnished to do so, subject to    *
 * the following conditions:                                                *
 *                                                                          *
 * The above copyright notice and this permission notice shall be included  *
 * in all copies or substantial portions of the Software.                   *
 *                                                                          *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS  *
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF               *
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   *
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY     *
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,     *
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE        *
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                   *
 ****************************************************************************/

#include "DWF_Shader_Collection_OpenGL.h"

using namespace DWF_Renderer;

//---------------------------------------------------------------------------
// Shader_Collection_OpenGL
//---------------------------------------------------------------------------
Shader_Collection_OpenGL::Shader_Collection_OpenGL()
{}
//---------------------------------------------------------------------------
Shader_Collection_OpenGL::~Shader_Collection_OpenGL()
{}
//---------------------------------------------------------------------------
std::string Shader_Collection_OpenGL::GetVertexShader(IEShaderType type)
{
    switch (type)
    {
        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Color:
            return "#version 130\n"
                   "precision mediump float;\n"
                   "attribute    vec3 dwf_aVertices;\n"
                   "attribute    vec4 dwf_aColor;\n"
                   "uniform      mat4 dwf_uProjection;\n"
                   "uniform      mat4 dwf_uView;\n"
                   "uniform      mat4 dwf_uModel;\n"
                   "varying lowp vec4 dwf_vColor;\n"
                   "void main(void)\n"
                   "{\n"
                   "    dwf_vColor  = dwf_aColor;\n"
                   "    gl_Position = dwf_uProjection * dwf_uView * dwf_uModel * vec4(dwf_aVertices, 1.0);\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Texture:
            return "#version 130\n"
                   "precision mediump float;\n"
                   "attribute    vec3 dwf_aVertices;\n"
                   "attribute    vec4 dwf_aColor;\n"
                   "attribute    vec2 dwf_aTexCoord;\n"
                   "uniform      mat4 dwf_uProjection;\n"
                   "uniform      mat4 dwf_uView;\n"
                   "uniform      mat4 dwf_uModel;\n"
                   "varying lowp vec4 dwf_vColor;\n"
                   "varying      vec2 dwf_vTexCoord;\n"
                   "void main(void)\n"
                   "{\n"
                   "    dwf_vColor    = dwf_aColor;\n"
                   "    dwf_vTexCoord = dwf_aTexCoord;\n"
                   "    gl_Position   = dwf_uProjection * dwf_uView * dwf_uModel * vec4(dwf_aVertices, 1.0);\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Texture_Normal:
            return "#version 130\n"
                   "precision mediump float;\n"
                   "attribute    vec3 dwf_aVertices;\n"
                   "attribute    vec3 dwf_aNormal;\n"
                   "attribute    vec4 dwf_aColor;\n"
                   "attribute    vec2 dwf_aTexCoord;\n"
                   "uniform      mat4 dwf_uProjection;\n"
                   "uniform      mat4 dwf_uView;\n"
                   "uniform      mat4 dwf_uModel;\n"
                   "varying lowp vec3 dwf_vNormal;\n"
                   "varying lowp vec4 dwf_vColor;\n"
                   "varying      vec2 dwf_vTexCoord;\n"
                   "void main(void)\n"
                   "{\n"
                   "    dwf_vNormal   = dwf_aNormal;\n"
                   "    dwf_vColor    = dwf_aColor;\n"
                   "    dwf_vTexCoord = dwf_aTexCoord;\n"
                   "    gl_Position   = dwf_uProjection * dwf_uView * dwf_uModel * vec4(dwf_aVertices, 1.0);\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Skybox:
            return "#version 130\n"
                   "precision mediump float;\n"
                   "attribute vec3 dwf_aVertices;\n"
                   "uniform   mat4 dwf_uProjection;\n"
                   "uniform   mat4 dwf_uView;\n"
                   "varying   vec3 dwf_vTexCoord;\n"
                   "void main()\n"
                   "{\n"
                   "    dwf_vTexCoord = dwf_aVertices;\n"
                   "    gl_Position   = dwf_uProjection * dwf_uView * vec4(dwf_aVertices, 1.0);\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Line:
            return "#version 130\n"
                   "precision mediump float;\n"
                   "attribute    vec3 dwf_aVertices;\n"
                   "attribute    vec4 dwf_aColor;\n"
                   "uniform      mat4 dwf_uProjection;\n"
                   "uniform      mat4 dwf_uView;\n"
                   "uniform      mat4 dwf_uModel;\n"
                   "varying lowp vec4 dwf_vColor;\n"
                   "void main(void)\n"
                   "{\n"
                   "    dwf_vColor  = dwf_aColor;\n"
                   "    gl_Position = dwf_uProjection * dwf_uView * dwf_uModel * vec4(dwf_aVertices, 1.0);\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Water:
            return "#version 120\n"
                   ""
                   "attribute vec3 dwf_aVertices;\n"
                   "attribute vec2 dwf_aTexCoord;\n"
                   ""
                   "varying vec2   dwf_vTexCoord;\n"
                   "varying vec3   dwf_vFragPos;\n"
                   "varying vec3   dwf_vNormal;\n"
                   "varying vec4   dwf_vClipSpace;\n"
                   "varying float  dwf_vWaveHeight;\n"
                   "varying vec3   dwf_vWorldPos;\n"
                   ""
                   "uniform mat4   dwf_uModel;\n"
                   "uniform mat4   dwf_uView;\n"
                   "uniform mat4   dwf_uProjection;\n"
                   "uniform float  dwf_uTime;\n"
                   "uniform float  dwf_uWaveStrength;\n"
                   ""
                   "void main()\n"
                   "{\n"
                   "    dwf_vTexCoord = dwf_aTexCoord;\n"
                   "    vec3 pos = dwf_aVertices;\n"
                   ""
                   "    // large ocean swells (slow, rolling waves)\n"
                   "    float swell1 = sin(pos.x * 0.15                + dwf_uTime * 0.3)  * cos(pos.z * 0.12 + dwf_uTime * 0.25);\n"
                   "    float swell2 = sin(pos.x * 0.18 - pos.z * 0.15 + dwf_uTime * 0.35) * 0.8;\n"
                   ""
                   "    // medium waves (wind waves)\n"
                   "    float wind1 = sin(pos.x * 0.5 + pos.z * 0.4 + dwf_uTime * 0.9) * 0.5;\n"
                   "    float wind2 = sin(pos.x * 0.7 - pos.z * 0.6 + dwf_uTime * 1.1) * 0.4;\n"
                   ""
                   "    // small surface ripples\n"
                   "    float ripple1 = sin(pos.x * 2.0 + pos.z * 1.8 + dwf_uTime * 1.8) * 0.2;\n"
                   "    float ripple2 = sin(pos.x * 2.8 - pos.z * 2.3 - dwf_uTime * 2.1) * 0.15;\n"
                   ""
                   "    // choppy detail\n"
                   "    float chop1 = sin(pos.x * 4.5 + dwf_uTime * 2.8) * 0.1;\n"
                   "    float chop2 = sin(pos.z * 5.2 - dwf_uTime * 3.2) * 0.08;\n"
                   ""
                   "    // combine all wave layers with proper weighting\n"
                   "    float finalWave = (swell1 * 1.2 + swell2 + wind1 + wind2 +\n"
                   "            ripple1 + ripple2 + chop1 + chop2) * dwf_uWaveStrength;\n"
                   "    pos.y          += finalWave;\n"
                   "    dwf_vWaveHeight = finalWave;\n"
                   "    dwf_vWorldPos   = pos;\n"
                   ""
                   "    // more accurate normal calculation with finer sampling\n"
                   "    float offset = 0.08;\n"
                   ""
                   "    // sample heights around current position\n"
                   "    vec2 offX = vec2(offset, 0.0);\n"
                   "    vec2 offZ = vec2(0.0,    offset);\n"
                   ""
                   "    float hL = (sin((pos.x - offset) * 0.15 + dwf_uTime * 0.3) * cos(pos.z * 0.12 + dwf_uTime * 0.25) * 1.2 +\n"
                   "                sin((pos.x - offset) * 0.18 - pos.z * 0.15 + dwf_uTime * 0.35) * 0.8 +\n"
                   "                sin((pos.x - offset) * 0.5  + pos.z * 0.4  + dwf_uTime * 0.9)  * 0.5 +\n"
                   "                sin((pos.x - offset) * 0.7  - pos.z * 0.6  + dwf_uTime * 1.1)  * 0.4 +\n"
                   "                sin((pos.x - offset) * 2.0  + pos.z * 1.8  + dwf_uTime * 1.8)  * 0.2 +\n"
                   "                sin((pos.x - offset) * 4.5                 + dwf_uTime * 2.8)  * 0.1) * dwf_uWaveStrength;\n"
                   ""
                   "    float hR = (sin((pos.x + offset) * 0.15 + dwf_uTime * 0.3) * cos(pos.z * 0.12 + dwf_uTime * 0.25) * 1.2 +\n"
                   "                sin((pos.x + offset) * 0.18 - pos.z * 0.15 + dwf_uTime * 0.35) * 0.8 +\n"
                   "                sin((pos.x + offset) * 0.5  + pos.z * 0.4  + dwf_uTime * 0.9)  * 0.5 +\n"
                   "                sin((pos.x + offset) * 0.7  - pos.z * 0.6  + dwf_uTime * 1.1)  * 0.4 +\n"
                   "                sin((pos.x + offset) * 2.0  + pos.z * 1.8  + dwf_uTime * 1.8)  * 0.2 +\n"
                   "                sin((pos.x + offset) * 4.5                 + dwf_uTime * 2.8)  * 0.1) * dwf_uWaveStrength;\n"
                   ""
                   "    float hD = (sin(pos.x * 0.15 + dwf_uTime * 0.3) * cos((pos.z - offset) * 0.12 + dwf_uTime * 0.25) * 1.2 +\n"
                   "                sin(pos.x * 0.18 - (pos.z - offset) * 0.15 + dwf_uTime * 0.35) * 0.8 +\n"
                   "                sin(pos.x * 0.5  + (pos.z - offset) * 0.4  + dwf_uTime * 0.9)  * 0.5 +\n"
                   "                sin(pos.x * 0.7  - (pos.z - offset) * 0.6  + dwf_uTime * 1.1)  * 0.4 +\n"
                   "                sin(pos.x * 2.0  + (pos.z - offset) * 1.8  + dwf_uTime * 1.8)  * 0.2 +\n"
                   "                sin((pos.z - offset) * 5.2                 - dwf_uTime * 3.2)  * 0.08) * dwf_uWaveStrength;\n"
                   ""
                   "    float hU = (sin(pos.x * 0.15 + dwf_uTime * 0.3) * cos((pos.z + offset) * 0.12 + dwf_uTime * 0.25) * 1.2 +\n"
                   "                sin(pos.x * 0.18 - (pos.z + offset) * 0.15 + dwf_uTime * 0.35) * 0.8 +\n"
                   "                sin(pos.x * 0.5  + (pos.z + offset) * 0.4  + dwf_uTime * 0.9)  * 0.5 +\n"
                   "                sin(pos.x * 0.7  - (pos.z + offset) * 0.6  + dwf_uTime * 1.1)  * 0.4 +\n"
                   "                sin(pos.x * 2.0  + (pos.z + offset) * 1.8  + dwf_uTime * 1.8)  * 0.2 +\n"
                   "                sin((pos.z + offset) * 5.2                 - dwf_uTime * 3.2)  * 0.08) * dwf_uWaveStrength;\n"
                   ""
                   "    vec3 tangentX = normalize(vec3(1.0, (hR - hL) / (2.0 * offset), 0.0));\n"
                   "    vec3 tangentZ = normalize(vec3(0.0, (hU - hD) / (2.0 * offset), 1.0));\n"
                   "    dwf_vNormal   = normalize(cross(tangentZ, tangentX));\n"
                   ""
                   "    dwf_vFragPos   = vec3(dwf_uModel * vec4(pos, 1.0));\n"
                   "    dwf_vClipSpace = dwf_uProjection * dwf_uView * vec4(dwf_vFragPos, 1.0);\n"
                   "    gl_Position    = dwf_vClipSpace;\n"
                   "}";

        default:
            return std::string();
    }
}
//---------------------------------------------------------------------------
std::string Shader_Collection_OpenGL::GetFragmentShader(IEShaderType type)
{
    switch (type)
    {
        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Color:
            return "#version 130\n"
                   "precision mediump float;\n"
                   "varying lowp vec4 dwf_vColor;\n"
                   "void main(void)\n"
                   "{\n"
                   "    gl_FragColor = dwf_vColor;\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Texture:
            return "#version 130\n"
                   "precision mediump float;\n"
                   "uniform      sampler2D dwf_sTexture;\n"
                   "varying lowp vec4      dwf_vColor;\n"
                   "varying      vec2      dwf_vTexCoord;\n"
                   "void main(void)\n"
                   "{\n"
                   "    gl_FragColor = dwf_vColor * texture2D(dwf_sTexture, dwf_vTexCoord);\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Texture_Normal:
            return "#version 130\n"
                   "precision mediump float;\n"
                   "uniform      sampler2D dwf_sTexture;\n"
                   "varying lowp vec3      dwf_vNormal;\n"
                   "varying lowp vec4      dwf_vColor;\n"
                   "varying      vec2      dwf_vTexCoord;\n"
                   "void main(void)\n"
                   "{\n"
                   "    gl_FragColor = dwf_vColor * texture2D(dwf_sTexture, dwf_vTexCoord);\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Texture_Alpha_Cut:
            return "#version 130\n"
                   "precision mediump float;\n"
                   "uniform      sampler2D dwf_sTexture;\n"
                   "varying lowp vec4      dwf_vColor;\n"
                   "varying      vec2      dwf_vTexCoord;\n"
                   "void main(void)\n"
                   "{\n"
                   "    gl_FragColor = dwf_vColor * texture2D(dwf_sTexture, dwf_vTexCoord);\n"
                   ""
                   "    if (gl_FragColor.a < 0.5)\n"
                   "        discard;\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Skybox:
            return "#version 330\n"
                   "precision mediump float;\n"
                   "uniform samplerCube dwf_sCubemap;\n"
                   "varying vec3        dwf_vTexCoord;\n"
                   "void main()\n"
                   "{\n"
                   "    gl_FragColor = texture(dwf_sCubemap, dwf_vTexCoord);\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Line:
            return "#version 130\n"
                   "precision mediump float;\n"
                   "varying lowp vec4 dwf_vColor;\n"
                   "void main(void)\n"
                   "{\n"
                   "    gl_FragColor = dwf_vColor;\n"
                   "}";

        case Shader_Collection_OpenGL::IEShaderType::IE_ST_Water:
            return "#version 120\n"
                   ""
                   "varying vec2  dwf_vTexCoord;\n"
                   "varying vec3  dwf_vFragPos;\n"
                   "varying vec3  dwf_vNormal;\n"
                   "varying float dwf_vWaveHeight;\n"
                   "varying vec3  dwf_vWorldPos;\n"
                   ""
                   "uniform float dwf_uTime;\n"
                   "uniform vec3  dwf_CameraPos;\n"
                   "uniform vec3  dwf_LightDir;\n"
                   "uniform vec3  dwf_WaterColor;\n"
                   "uniform vec3  dwf_DeepWaterColor;\n"
                   "uniform float dwf_WaterClearness;\n"
                   ""
                   "float hash(vec2 p)\n"
                   "{\n"
                   "    p = fract(p * vec2(443.897, 441.423));\n"
                   "    p += dot(p, p.yx + 19.19);\n"
                   "    return fract(p.x * p.y);\n"
                   "}\n"
                   ""
                   "float noise(vec2 p)\n"
                   "{\n"
                   "    vec2 i = floor(p);\n"
                   "    vec2 f = fract(p);\n"
                   ""
                   "    // quintic interpolation for smoother results\n"
                   "    f = f * f * f * (f * (f * 6.0 - 15.0) + 10.0);\n"
                   ""
                   "    float a = hash(i);\n"
                   "    float b = hash(i + vec2(1.0, 0.0));\n"
                   "    float c = hash(i + vec2(0.0, 1.0));\n"
                   "    float d = hash(i + vec2(1.0, 1.0));\n"
                   ""
                   "    return mix(mix(a, b, f.x), mix(c, d, f.x), f.y);\n"
                   "}\n"
                   ""
                   "// high quality FBM with 5 octaves\n"
                   "float fbm(vec2 p)\n"
                   "{\n"
                   "    float value     = 0.0;\n"
                   "    float amplitude = 0.5;\n"
                   "    float frequency = 1.0;\n"
                   ""
                   "    for (int i = 0; i < 5; ++i)\n"
                   "    {\n"
                   "        value     += amplitude * noise(p * frequency);\n"
                   "        frequency *= 2.1;\n"
                   "        amplitude *= 0.48;\n"
                   "    }\n"
                   "    return value;\n"
                   "}\n"
                   ""
                   "float caustics(vec2 uv, float dwf_uTime)\n"
                   "{\n"
                   "    vec2  p  = uv * 4.0;\n"
                   ""
                   "    float c1 = fbm(p       + dwf_uTime * 0.08);\n"
                   "    float c2 = fbm(p * 1.3 - dwf_uTime * 0.1 + vec2(100.0, 100.0));\n"
                   "    float c3 = fbm(p * 1.7 + dwf_uTime * 0.06);\n"
                   ""
                   "    float caustic = c1 * c2 + c3 * 0.5;\n"
                   "    caustic       = pow(max(caustic, 0.0), 3.0);\n"
                   ""
                   "    return caustic * 2.5;\n"
                   "}\n"
                   ""
                   "void main()\n"
                   "{\n"
                   "    vec3 norm    = normalize(dwf_vNormal);\n"
                   "    vec3 viewDir = normalize(dwf_CameraPos - dwf_vFragPos);\n"
                   ""
                   "    // physically accurate Fresnel (Schlick's approximation)\n"
                   "    float F0      = 0.02; // water's reflectance at normal incidence\n"
                   "    float NdotV   = max(dot(norm, viewDir), 0.0);\n"
                   "    float fresnel = F0 + (1.0 - F0) * pow(1.0 - NdotV, 5.0);\n"
                   ""
                   "    // enhanced surface distortion for realism\n"
                   "    vec2 distortion1 = vec2(\n"
                   "        fbm(dwf_vTexCoord * 2.5 + dwf_uTime * 0.03),\n"
                   "        fbm(dwf_vTexCoord * 2.5 + dwf_uTime * 0.03 + 100.0)\n"
                   "    ) * 0.04;\n"
                   ""
                   "    vec2 distortion2 = vec2(\n"
                   "        noise(dwf_vTexCoord * 5.0 - dwf_uTime * 0.05 + 50.0),\n"
                   "        noise(dwf_vTexCoord * 5.0 - dwf_uTime * 0.05 + 150.0)\n"
                   "    ) * 0.02;\n"
                   ""
                   "    vec2 distortedCoord = dwf_vTexCoord + distortion1 + distortion2;\n"
                   ""
                   "    // improved caustics\n"
                   "    float causticsEffect = caustics(distortedCoord, dwf_uTime);\n"
                   ""
                   "    // realistic foam on wave crests\n"
                   "    float foamThreshold = 0.35;\n"
                   "    float foamAmount    = smoothstep(foamThreshold, foamThreshold + 0.3, dwf_vWaveHeight);\n"
                   "    float foamPattern   = fbm(dwf_vWorldPos.xz * 3.0 + dwf_uTime * 0.5) * 0.5 + 0.5;\n"
                   "    float foam          = foamAmount * foamPattern * 0.6;\n"
                   ""
                   "    // sun lighting\n"
                   "    vec3 lightDirection = normalize(-dwf_LightDir);\n"
                   "    float diffuse       = max(dot(norm, lightDirection), 0.0);\n"
                   ""
                   "    // enhanced specular with sun color\n"
                   "    vec3 halfDir    = normalize(lightDirection + viewDir);\n"
                   "    float specAngle = max(dot(norm, halfDir), 0.0);\n"
                   "    float specular  = pow(specAngle, 256.0); // sharper highlights\n"
                   ""
                   "    // stronger specular on peaks\n"
                   "    specular *= (1.0 + dwf_vWaveHeight * 2.0);\n"
                   ""
                   "    // subsurface scattering (light through wave peaks)\n"
                   "    vec3  H           = normalize(lightDirection + norm * 0.4);\n"
                   "    float subsurface  = pow(clamp(dot(viewDir, -H), 0.0, 1.0), 4.0) * 0.6;\n"
                   "    subsurface       *= max(0.0, dwf_vWaveHeight); // only on elevated waves\n"
                   ""
                   "    // depth-based color with more realistic variation\n"
                   "    float depthFactor = mix(0.2, 1.0, fresnel);\n"
                   ""
                   "    // darker, more realistic water colors\n"
                   "    vec3 shallowColor = dwf_WaterColor     * vec3(0.8, 1.0, 1.1);   // slight cyan tint\n"
                   "    vec3 deepColor    = dwf_DeepWaterColor * vec3(0.7, 0.85, 0.95); // deep blue-green\n"
                   ""
                   "    // mix based on depth and viewing angle\n"
                   "    vec3 baseColor = mix(shallowColor, deepColor, depthFactor);\n"
                   ""
                   "    // darken water in troughs, brighten on peaks\n"
                   "    baseColor *= mix(0.7, 1.3, smoothstep(-0.5, 0.5, dwf_vWaveHeight));\n"
                   ""
                   "    // sun color (warm yellow-white)\n"
                   "    vec3 sunColor = vec3(1.0, 0.95, 0.85);\n"
                   ""
                   "    // ambient light (darker for more realistic look)\n"
                   "    vec3 ambient = baseColor * 0.3;\n"
                   ""
                   "    // diffuse lighting\n"
                   "    vec3 diffuseLight = baseColor * sunColor * diffuse * 0.6;\n"
                   ""
                   "    // specular highlights (sun reflections)\n"
                   "    vec3 specularLight = sunColor * specular * 2.5 * fresnel;\n"
                   ""
                   "    // subsurface scattering (light through waves)\n"
                   "    vec3 subsurfaceLight = vec3(0.1, 0.4, 0.5) * subsurface;\n"
                   ""
                   "    // caustics (underwater light patterns) - only visible at certain angles\n"
                   "    vec3 causticsLight = vec3(0.5, 0.7, 0.9) * causticsEffect * 0.15 * (1.0 - fresnel);\n"
                   ""
                   "    // foam (white caps)\n"
                   "    vec3 foamColor = vec3(1.0, 1.0, 1.0) * foam;\n"
                   ""
                   "    // combine all lighting\n"
                   "    vec3 color = ambient + diffuseLight + specularLight + subsurfaceLight + causticsLight + foamColor;\n"
                   ""
                   "    // add slight color variation based on viewing angle (atmospheric perspective)\n"
                   "    vec3 skyTint = vec3(0.7, 0.85, 1.0);\n"
                   "    color        = mix(color, color * skyTint, fresnel * 0.2);\n"
                   ""
                   "    // enhanced edge darkening (water appears darker at grazing angles in real life)\n"
                   "    color *= mix(0.8, 1.0, NdotV * 0.5 + 0.5);\n"
                   ""
                   "    // dynamic alpha for realistic transparency\n"
                   "    float alpha = mix(dwf_WaterClearness * 0.7, 0.98, fresnel);\n"
                   "    alpha       = mix(alpha, 1.0, foam); // Foam is opaque\n"
                   ""
                   "    gl_FragColor = vec4(color, alpha);\n"
                   "}";

        default:
            return std::string();
    }
}
//---------------------------------------------------------------------------
