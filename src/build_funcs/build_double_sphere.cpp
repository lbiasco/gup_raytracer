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
	
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->SetCenter(0.0);
	sphere_ptr->SetRadius(85);
	sphere_ptr->SetColor(1, 0, 0);  // red
	AddObject(sphere_ptr);	

	sphere_ptr = new Sphere;
	sphere_ptr->SetCenter(0.0);
	sphere_ptr->SetRadius(75);
	sphere_ptr->SetColor(0, 0, 1);  // red
	AddObject(sphere_ptr);	
}
