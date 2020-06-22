void 												
World::Build(void) {
    vp_.SetHRes(200);
	vp_.SetVRes(200);
	vp_.SetPixelSize(1.0);
	vp_.SetGamma(1.0);
	
	background_color_ = kWhite;
	tracer_ptr_ = new SingleSphere(this); 
	
	sphere_.SetCenter(Point3D(50.0, 0.0, 0.0));
	sphere_.SetRadius(150);
}
