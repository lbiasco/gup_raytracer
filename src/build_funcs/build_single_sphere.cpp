void 												
World::Build(void) {
    vp_.SetHRes(100);
	vp_.SetVRes(100);
	vp_.SetPixelSize(3);
	vp_.SetGamma(1.0);
	
	background_color_ = kWhite;
	tracer_ptr_ = new SingleSphere(this); 
	
	sphere_.SetCenter(Point3D(50.0, 0.0, 0.0));
	sphere_.SetRadius(100);
}
