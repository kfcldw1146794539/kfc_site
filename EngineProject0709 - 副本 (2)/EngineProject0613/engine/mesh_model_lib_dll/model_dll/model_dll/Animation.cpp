#include"Animation.h"

AnimationManager* g_animation_manager = NULL;
//Animation::Animation(string name, float* oigin_value, float targe_value, int ani_steps)
//{
//	m_Animation_Name = name;
//	m_Ani_target = oigin_value;
//	m_Ani_target_original = *oigin_value;
//	m_Ani_targets.clear();
//	m_Ani_target_originals.clear();
//	m_target_counts = 0;
//	m_interpolator = new BezierInterpolator(targe_value, ani_steps);
//	m_loop_reverse_flag = false;
//	m_create_ok = false;
//	m_loop_to_max = false;
//	if (g_animation_manager)
//	{
//		m_create_ok = g_animation_manager->Add_Animation(name, this);
//	}
//
//}

//Animation::Animation(string name, vector<float*> oigin_value, int target_counts, float targe_value, int ani_steps)
//{
//
//	m_Animation_Name = name;
//	m_Ani_target = NULL;
//	m_Ani_target_original = 0.0f;
//	m_Ani_targets.clear();
//	m_Ani_target_originals.clear();
//	m_target_counts = target_counts;
//	m_interpolator = new BezierInterpolator(targe_value, ani_steps);
//	m_loop_reverse_flag = false;
//	m_create_ok = false;
//	m_loop_to_max = false;
//	for (int i = 0; i < m_target_counts;i++)
//	{
//		m_Ani_targets.push_back(oigin_value[i]);
//		m_Ani_target_originals.push_back(*oigin_value[i]);
//	}
//	if (g_animation_manager)
//	{
//		m_create_ok = g_animation_manager->Add_Animation(name, this);
//	}
//
//}
Animation::Animation(string name, float* oigin_value, vector<AniPointData> Ani_point_data)
{
	m_Animation_Name = name;
	m_Ani_target = oigin_value;
	m_Ani_target_original = *oigin_value;
	m_Ani_targets.clear();
	m_Ani_target_originals.clear();
	m_target_counts = 0;
	m_interpolator = new BezierInterpolator_2(Ani_point_data);
	m_loop_reverse_flag = false;
	m_create_ok = false;
	m_loop_to_max = false;
	if (g_animation_manager)
	{
		m_create_ok = g_animation_manager->Add_Animation(name, this);
	}

}
Animation::Animation(string name, vector<float*> oigin_value, int target_counts, vector<AniPointData> Ani_point_data)
{

	m_Animation_Name = name;
	m_Ani_target = NULL;
	m_Ani_target_original = 0.0f;
	m_Ani_targets.clear();
	m_Ani_target_originals.clear();
	m_target_counts = target_counts;
	m_interpolator = new BezierInterpolator_2(Ani_point_data);
	m_loop_reverse_flag = false;
	m_create_ok = false;
	m_loop_to_max = false;
	for (int i = 0; i < m_target_counts; i++)
	{
		m_Ani_targets.push_back(oigin_value[i]);
		m_Ani_target_originals.push_back(*oigin_value[i]);
	}
	if (g_animation_manager)
	{
		m_create_ok = g_animation_manager->Add_Animation(name, this);
	}

}
Animation::~Animation()
{
	delete m_interpolator;
}


bool Animation::Play(bool play_reverse)
{
	m_ani_state = PLAY;
	m_play_reverse_flag = play_reverse;
	if (m_play_reverse_flag == false)
		m_interpolator_state = 0;
	else
		m_interpolator_state = m_interpolator->m_steps;

	return true;
}

bool Animation::Pause()
{
	m_ani_state = PAUSE;
	return true;

}

bool Animation::stop()
{
	m_ani_state = STOP;
	return true;
}

bool Animation::LoopPlay(int times, bool reverse_flag, bool loop_to_max)
{
	if (reverse_flag)
	{
		m_ani_state = LOOP_REVERSE;
	}
	else
	{
		m_ani_state = LOOP;
		m_loop_to_max = loop_to_max;
	}
	return true;

}



void Animation::update(float delta_time)
{
	switch (m_ani_state)
	{
	case PLAY:
		if (!m_play_reverse_flag)
		{
			if (m_interpolator_state >= (m_interpolator->m_steps + 1))
			{
				printf("!m_play_reverse_flag m_interpolator_state >= (m_interpolator->m_steps + 1)  m_interpolator_state=%d\n", m_interpolator_state);
				m_interpolator_state = 0;
				m_ani_state = FIN;
				//m_play_reverse_flag = true;
				//*m_Ani_target = m_Ani_target_original;
			}
			else
			{

				if (m_Ani_target)
					* m_Ani_target = m_interpolator->m_interpolation_Points[m_interpolator_state].y;
				if (m_target_counts != 0)
				{
					for (int i = 0; i < m_target_counts; i++)
					{
						*m_Ani_targets[i] = m_interpolator->m_interpolation_Points[m_interpolator_state].y;
					}
				}
				++m_interpolator_state;
				printf("!m_play_reverse_flag  m_interpolator_state=%d\n", m_interpolator_state);
			}

		}
		if (m_play_reverse_flag)
		{
			if (m_interpolator_state >= (m_interpolator->m_steps + 1))
				m_interpolator_state = m_interpolator->m_steps;
			//*m_Ani_target = m_interpolator->m_interpolation_Point[m_interpolator_state].y;
			if (m_Ani_target)
			{
				printf("m_play_reverse_flag  m_interpolator_state=%d\n", m_interpolator_state);
				*m_Ani_target = m_interpolator->m_interpolation_Points[m_interpolator_state].y;
			}
			if (m_target_counts != 0)
			{
				for (int i = 0; i < m_target_counts; i++)
				{
					*m_Ani_targets[i] = m_interpolator->m_interpolation_Points[m_interpolator_state].y;
				}
			}
			--m_interpolator_state;
			if (m_interpolator_state < 0)
			{
				m_interpolator_state = 0;
				m_ani_state = FIN;
				//m_play_reverse_flag = false;
			}
		}
		break;
	case PAUSE:
		m_interpolator_state;
		break;

	case STOP:
		m_interpolator_state = 0;
		//*m_Ani_target = m_Ani_target_original;
		if (m_Ani_target)
		{
			*m_Ani_target = m_Ani_target_original;
		}
		if (m_target_counts != 0)
		{
			for (int i = 0; i < m_target_counts; i++)
			{
				*m_Ani_targets[i] = m_Ani_target_originals[i];
			}
		}
		break;

	case LOOP:
		if (m_interpolator_state >= (m_interpolator->m_steps + 1))
		{
			m_interpolator_state = 0;
			//m_ani_state = FIN;
			//*m_Ani_target = m_Ani_target_original;
			if (m_Ani_target)
			{

				if (m_loop_to_max)
				{
					//m_ani_state = LOOP_TO_MAX;

				}
				else
				{
					*m_Ani_target = m_Ani_target_original;
				}

			}
			if (m_target_counts != 0)
			{
				for (int i = 0; i < m_target_counts; i++)
				{

					if (m_loop_to_max)
					{
						if (i == m_interpolator->m_index_max_interpolation_velue)
						{
							m_ani_state = LOOP_TO_MAX;
						}
					}
					else
					{
						*m_Ani_targets[i] = m_Ani_target_originals[i];
					}

				}
				//m_interpolator_state = m_interpolator->m_steps + 1;
			}
		}
		else
		{
			//*m_Ani_target = m_interpolator->m_interpolation_Point[m_interpolator_state].y;
			if (m_Ani_target)
			{

				*m_Ani_target = m_interpolator->m_interpolation_Points[m_interpolator_state].y;
				if (m_loop_to_max)
				{
					if (m_interpolator->m_index_max_interpolation_velue == m_interpolator_state)
						m_ani_state = LOOP_TO_MAX;

				}

			}
			if (m_target_counts != 0)
			{
				for (int i = 0; i < m_target_counts; i++)
				{
					*m_Ani_targets[i] = m_interpolator->m_interpolation_Points[m_interpolator_state].y;
				}
				if (m_loop_to_max)
				{
					if (m_interpolator->m_index_max_interpolation_velue == m_interpolator_state)
					{
						m_ani_state = LOOP_TO_MAX;
						break;
					}



				}

			}
			++m_interpolator_state;
		}


		break;

	case LOOP_TO_MAX:
		if (m_Ani_target)
		{
			*m_Ani_target = *m_Ani_target + m_interpolator->m_max_interpolation_velue;
			if (abs(*m_Ani_target) > abs(m_interpolator->m_targe_value))
			{
				float a = m_interpolator->m_interpolation_Points[0].y;
				float b = *m_Ani_target - m_interpolator->m_targe_value;
				*m_Ani_target = a + b;
			}

		}
		if (m_target_counts != 0)
		{

			for (int i = 0; i < m_target_counts; i++)
			{
				*m_Ani_targets[i] = *m_Ani_targets[i] + m_interpolator->m_max_interpolation_velue;
				if (abs(*m_Ani_targets[i]) > abs(m_interpolator->m_targe_value))
				{
					float a = m_interpolator->m_interpolation_Points[0].y;
					float b = *m_Ani_targets[i] - m_interpolator->m_targe_value;
					*m_Ani_targets[i] = a + b;

				}

			}
		}

		break;

	case LOOP_REVERSE:
		if (m_loop_reverse_flag == false)
		{
			if (m_interpolator_state >= (m_interpolator->m_steps + 1))
			{
				m_interpolator_state = m_interpolator->m_steps;
				m_loop_reverse_flag = true;
			}
			else
			{
				//*m_Ani_target = m_interpolator->m_interpolation_Point[m_interpolator_state].y;
				if (m_Ani_target)
				{
					*m_Ani_target = m_interpolator->m_interpolation_Points[m_interpolator_state].y;
				}
				if (m_target_counts != 0)
				{
					for (int i = 0; i < m_target_counts; i++)
					{
						*m_Ani_targets[i] = m_interpolator->m_interpolation_Points[m_interpolator_state].y;
					}
				}
				++m_interpolator_state;
			}



		}
		if (m_loop_reverse_flag == true)
		{
			if (m_interpolator_state < 0)
			{
				m_interpolator_state = 0;
				m_loop_reverse_flag = false;
			}
			else
			{
				//*m_Ani_target = m_interpolator->m_interpolation_Point[m_interpolator_state].y;
				if (m_Ani_target)
				{
					*m_Ani_target = m_interpolator->m_interpolation_Points[m_interpolator_state].y;
				}
				if (m_target_counts != 0)
				{
					for (int i = 0; i < m_target_counts; i++)
					{
						*m_Ani_targets[i] = m_interpolator->m_interpolation_Points[m_interpolator_state].y;
					}
				}
				--m_interpolator_state;
			}


		}
		break;


	default:
		break;

	}

}

bool Animation::CheckCreateOK()
{
	return m_create_ok;
}


AnimationManager::AnimationManager() { g_animation_manager = this; }

AnimationManager::~AnimationManager()
{
	for (map<string, Animation*>::iterator iter = m_anis.begin(); iter != m_anis.end(); ++iter)
	{
		delete iter->second;
	}
}

bool AnimationManager::Add_Animation(string name, Animation* ani)
{
	map<string, Animation*>::iterator iter = m_anis.find(name);
	if (iter != m_anis.end())
		return false;
	m_anis[name] = ani;
	return true;
}

bool AnimationManager::PlayAnimation(string name)
{
	map<string, Animation*>::iterator iter = m_anis.find(name);
	if (iter == m_anis.end())
		return false;
	//m_anis[name] = ani;
	bool f = false;
	//if (name == "bonnet_turn")
	//{
	//	//f = iter->second->LoopPlay(-1,true);
	//	f = iter->second->Play(false);
	//}
	//if (name == "ani_wheel_run")
	//	//f = iter->second->LoopPlay(-1,true);
	//	f = iter->second->Play(false);
	//if (name == "r_door_turn")
	////	f = iter->second->LoopPlay(-1, true);
	//	f = iter->second->Play(false);
	//if (name == "l_door_turn")
	////	f = iter->second->LoopPlay(-1, true);
	//	f = iter->second->Play(false);a->PlayAnimation("bonnet_move");
	if (name == "bonnet_move")
		f = iter->second->LoopPlay(-1, true);
	if (name == "ani_wheel_turn")
	{
		//f = iter->second->LoopPlay(-1,true);
		if (iter->second->m_play_reverse_flag == true)
		{
			printf("iter->second->m_play_reverse_flag == true\n");
			f = iter->second->Play(false);
		}
		else
		{
			printf("iter->second->m_play_reverse_flag == false\n");
			f = iter->second->Play(true);
		}
	}
	if (name == "ani_wheel_run")
	{

		if (iter->second->m_play_reverse_flag == true)
		{
			printf("iter->second->m_play_reverse_flag == true\n");
			f = iter->second->Play(false);
		}
		else
		{
			printf("iter->second->m_play_reverse_flag == false\n");
			f = iter->second->Play(true);
		}
	}
	if (name == "l_door_turn")
	{

		if (iter->second->m_play_reverse_flag == true)
		{
			printf("iter->second->m_play_reverse_flag == true\n");
			f = iter->second->Play(false);
		}
		else
		{
			printf("iter->second->m_play_reverse_flag == false\n");
			f = iter->second->Play(true);
		}
	}
	if (name == "r_door_turn")
	{

		if (iter->second->m_play_reverse_flag == true)
		{
			printf("iter->second->m_play_reverse_flag == true\n");
			f = iter->second->Play(false);
		}
		else
		{
			printf("iter->second->m_play_reverse_flag == false\n");
			f = iter->second->Play(true);
		}
	}
	if (name == "back_skylight_turn")
	{

		if (iter->second->m_play_reverse_flag == true)
		{

			f = iter->second->Play(false);
		}
		else
		{

			f = iter->second->Play(true);
		}
	}
	if (name == "all_wheel_run")
	{

		if (iter->second->m_play_reverse_flag == true)
		{

			f = iter->second->Play(false);
		}
		else
		{

			f = iter->second->Play(true);
		}
	}
	if (name == "front_wheel_turn")
	{


		if (iter->second->m_play_reverse_flag == true)
		{

			f = iter->second->Play(false);
		}
		else
		{

			f = iter->second->Play(true);
		}
	}
	if (name == "left_back_door_move")
	{


		if (iter->second->m_play_reverse_flag == true)
		{

			f = iter->second->Play(false);
		}
		else
		{

			f = iter->second->Play(true);
		}
	}
	if (name == "left_back_door_move1")
	{


		if (iter->second->m_play_reverse_flag == true)
		{

			f = iter->second->Play(false);
		}
		else
		{

			f = iter->second->Play(true);
		}
	}
	if (name == "right_back_door_move")
	{


		if (iter->second->m_play_reverse_flag == true)
		{
			printf("iter->second->m_play_reverse_flag == true\n");
			f = iter->second->Play(false);
		}
		else
		{
			printf("iter->second->m_play_reverse_flag == false\n");
			f = iter->second->Play(true);
		}
	}
	if (name == "right_back_door_move1")
	{


		if (iter->second->m_play_reverse_flag == true)
		{
			printf("iter->second->m_play_reverse_flag == true\n");
			f = iter->second->Play(false);
		}
		else
		{
			printf("iter->second->m_play_reverse_flag == false\n");
			f = iter->second->Play(true);
		}
	}
	if (name == "front_skyligt_move")
	{


		if (iter->second->m_play_reverse_flag == true)
		{
			printf("iter->second->m_play_reverse_flag == true\n");
			f = iter->second->Play(false);
		}
		else
		{
			printf("iter->second->m_play_reverse_flag == false\n");
			f = iter->second->Play(true);
		}
	}
	if (name == "front_skyligt_up")
	{


		if (iter->second->m_play_reverse_flag == true)
		{
			printf("iter->second->m_play_reverse_flag == true\n");
			f = iter->second->Play(false);
		}
		else
		{
			printf("iter->second->m_play_reverse_flag == false\n");
			f = iter->second->Play(true);
		}
	}
	if (name == "back_skyligt_move")
	{


		if (iter->second->m_play_reverse_flag == true)
		{
			printf("iter->second->m_play_reverse_flag == true\n");
			f = iter->second->Play(false);
		}
		else
		{
			printf("iter->second->m_play_reverse_flag == false\n");
			f = iter->second->Play(true);
		}
	}
	if (name == "back_skyligt_up")
	{


		if (iter->second->m_play_reverse_flag == true)
		{
			printf("iter->second->m_play_reverse_flag == true\n");
			f = iter->second->Play(false);
		}
		else
		{
			printf("iter->second->m_play_reverse_flag == false\n");
			f = iter->second->Play(true);
		}
	}
	return f;
	//return iter->second->Play();
}