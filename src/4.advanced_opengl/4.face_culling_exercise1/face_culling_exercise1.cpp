float vertices[] = {
    // back face
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right    
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right              
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left                
    // front face
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right        
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left        
    // left face
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left       
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
    // right face
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right      
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right          
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
    // bottom face          
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left        
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
    // top face
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right                 
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // bottom-left  
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f  // top-left              
};

/* Also make sure to add a call to OpenGL to specify that triangles defined by a clockwise ordering 
   are now 'front-facing' triangles so the cube is rendered as normal:
   glFrontFace(GL_CW);
*/