void 												
World::Build(void) {

    int num_samples = 16;

    vp_.SetHRes(200);
	vp_.SetVRes(200);
	vp_.SetPixelSize(1.0);
    vp_.SetSampler(new MultiJittered(num_samples));
	vp_.SetGamma(1.0);

	tracer_ptr_ = new MultipleObjects(this); 
	
	background_color_ = kWhite;
	
	// use access functions to set centre and radius
	
	Plane* plane_ptr = new Plane;
	plane_ptr->SetPoint(Point3D(0, 1, 0));
	plane_ptr->SetNormal(Normal(0, 1, 0));
	plane_ptr->SetColor(1, 0, 0);  // red
	AddObject(plane_ptr);
}