void 												
World::Build(void) {

    int num_samples = 16;

    vp_.SetHRes(200);
	vp_.SetVRes(200);
	vp_.SetPixelSize(1.0);
    vp_.SetSampler(new MultiJittered(num_samples));
	vp_.SetGamma(1.0);

    Point3D cam_eye(0, 0, 100);
    Point3D cam_lookat(0, 0, 0);
    float cam_d = 10;
    Pinhole *ptr = new Pinhole(cam_eye, cam_lookat, cam_d);
    ptr->zoom_ = 1;
    camera_ptr_ = ptr;

	tracer_ptr_ = new MultipleObjects(this); 
	
	background_color_ = kWhite;
	
	// use access functions to set centre and radius
	
	Plane* plane_ptr = new Plane;
	plane_ptr->SetPoint(Point3D(0, 1, 0));
	plane_ptr->SetNormal(Normal(0, 1, 0));
	plane_ptr->SetColor(1, 0, 0);  // red
	AddObject(plane_ptr);
}
