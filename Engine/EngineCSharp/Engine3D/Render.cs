using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace E3DEngine
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi, Pack = 1)]
    public struct Vertex
    {
        private Single[] Position;
        private Single[] Normals;
        private Single[] Color;
        private Single[] UV;
        private Single[] Tangent;
        private Single[] BoneIndex;
        private Single[] BoneWeight;
        private Single[] TranformPosition;
        private Single[] TransformScale;
        private Single[] TransformRotate;
        private Single ShaderIndex;

        public void Init()
        {
            Position = new Single[3] { 0,0,0};
            Normals = new Single[3] { 0, 0, 0 };
            Color = new Single[4] { 0, 0, 0 ,0};
            UV = new Single[2] { 0, 0};
            Tangent = new Single[3] { 0, 0, 0 };
            ShaderIndex = 0;
            BoneIndex = new Single[4] { 0, 0, 0,0 };
            BoneWeight = new Single[4] { 0, 0, 0, 0 };
            TranformPosition = new Single[3] { 0, 0, 0 };
            TransformScale = new Single[3] { 0, 0, 0 };
            TransformRotate = new Single[3] { 0, 0, 0 };
        }

        public int GetSize()
        {
            int size = Position.Length + Normals.Length + Color.Length + UV.Length + Tangent.Length + 1 +
               BoneIndex.Length + TranformPosition.Length + TransformRotate.Length + TransformScale.Length;
            return size;
        }
        
        public void SetPosition(float x, float y, float z)
        {
            Position[0] = x;
            Position[1] = y;
            Position[2] = z;
        }

        public void SettextureCoord(float u, float v)
        {
            UV[0] = u;
            UV[1] = v;
        }

        public void SetNormal(float x, float y, float z)
        {
            Normals[0] = x;
            Normals[1] = y;
            Normals[2] = z;
        }

        public void SetColor(float r, float g, float b, float a)
        {
            Color[0] = r;
            Color[1] = g;
            Color[2] = b;
            Color[3] = a;
        }

        public void SetTangent(float x, float y, float z)
        {
            Tangent[0] = x;
            Tangent[1] = y;
            Tangent[2] = z;
        }
        
        public void SetTransformPosition(float x, float y, float z)
        {
            TranformPosition[0] = x;
            TranformPosition[1] = y;
            TranformPosition[2] = z;
        }

        public void SetTransformScale(float x, float y, float z)
        {
            TransformScale[0] = x;
            TransformScale[1] = y;
            TransformScale[2] = z;
        }

        public void SetTransformRotate(float x, float y, float z)
        {
            TransformRotate[0] = x;
            TransformRotate[1] = y;
            TransformRotate[2] = z;
        }
    }

    public enum eDrawModule
    {
        TRIANGLE_STRIP,
        TRIANGLES,
        LINE_STRIP,
        LINES,
        POINTS,
    }

    public enum eRenderIndex
    {
        None,
        LowMost,
        Normal,
        Transparent,
        TopMost,
    }

    public class Render : Object
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern Render createRenderer(uint materialID);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private static extern Render createRendererWithoutParam();

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void setVertex2Render(Vertex[] vertexs, uint[] indexs);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern void setDrawModule(uint module);

        [MethodImpl(MethodImplOptions.InternalCall)]
        private extern uint getDrawModule();

        public eRenderIndex RenderIndex
        {
            [MethodImpl(MethodImplOptions.InternalCall)]
            get;
            [MethodImpl(MethodImplOptions.InternalCall)]
            set;
        }

        public eDrawModule DrawModule
        {
            set
            {
                setDrawModule((uint)value);
            }
            get
            {
                return (eDrawModule)getDrawModule();
            }
        }

        public static Render CreateRenderer(Material material)
        {
            return createRenderer(material.ID);
        }

        public static Render CreateRenderer()
        {
            return createRendererWithoutParam();
        }

        public void DrawElements(List<Vertex> vertexs, List<uint> indexs)
        {
            Vertex[] vertexArray = vertexs.ToArray();
            uint[] indexArray = indexs.ToArray();
            setVertex2Render(vertexArray, indexArray);
        }
    }
}
