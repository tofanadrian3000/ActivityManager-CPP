//#include "Tests.h"
//
//void testActivity() {
//	Activity activity = Activity("default", "default", "default", 1);
//	assert(activity.getDescription() == "default");
//	assert(activity.getTitle() == "default");
//	assert(activity.getType() == "default");
//	assert(activity.getDuration() == 1);
//	Activity newActivity = Activity("Lord of the rings", "asd", "fantasy", 180);
//	assert(newActivity.getDescription() == "asd");
//	assert(newActivity.getTitle() == "Lord of the rings");
//	assert(newActivity.getType() == "fantasy");
//	assert(newActivity.getDuration() == 180);
//	assert((newActivity == activity) == false);
//	assert((newActivity != activity) == true);
//	activity.setTitle("asd");
//	assert(activity.getTitle() == "asd");
//	activity.setDescription("asd");
//	assert(activity.getDescription() == "asd");
//	activity.setType("asd");
//	assert(activity.getType() == "asd");
//	activity.setDuration(5);
//	assert(activity.getDuration() == 5);
//	activity = newActivity;
//	assert(activity.getTitle() == "Lord of the rings");
//	assert(activity.getDescription() == "asd");
//	assert(activity.getType() == "fantasy");
//	assert(activity.getDuration() == 180);
//}
//
//void testRepository() {
//	Activity activity1 = Activity("asd", "asd", "asd", 1);
//	Activity activity2 = Activity("abc", "asd", "asd", 2);
//	Activity activity3 = Activity("asd", "asd", "asd", 3);
//	Repository<Activity> repo = Repository<Activity>();
//	assert(repo.size() == 0);
//	repo.add(activity1);
//	assert(repo.size() == 1);
//	try {
//		repo.add(activity3);
//		assert(false);
//	}
//	catch (RepositoryException& ex) { assert(true); assert(ex.getMsg() != ""); }
//	assert(repo.size() == 1);
//	try {
//		repo.update(activity2, activity3);
//		assert(false);
//	}
//	catch (RepositoryException) { assert(true); }
//	std::vector<Activity> elems = repo.getAll();
//	assert(elems.size() == 1);
//	assert(repo.exist(activity2) == false);
//	repo.update(activity1, activity2);
//
//	try {
//		repo.remove(activity1);
//		assert(false);
//	}
//	catch (RepositoryException) { assert(true); }
//	repo.remove(activity2);
//	assert(repo.size() == 0);
//	assert(repo.exist(activity2) == false);
//
//}
//void testService() {
//	std::ofstream out("test.txt");
//	out << "";
//	Service service = Service("test.txt");
//	assert(service.size() == 0);
//	try {
//		const Activity a = service.getActivity("asd");
//		assert(false);
//	}
//	catch (ServiceException) { assert(true); }
//	service.addActivity("title", "description", "type", "1");
//	assert(service.size() == 1);
//	try {
//		service.addActivity("title", "asd", "asd", "2");
//		assert(false);
//	}
//	catch (ServiceException& ex) { assert(true); assert(ex.getMsg() != ""); }
//	assert(service.size() == 1);
//	try {
//		service.addActivity("", "", "", "");
//		assert(false);
//	}
//	catch (ServiceException) { assert(true); }
//	try {
//		service.updateActivity("", "", "", "");
//		assert(false);
//	}
//	catch (ServiceException) { assert(true); }
//	try {
//		service.removeActivity("");
//		assert(false);
//	}
//	catch (ServiceException) { assert(true); }
//	service.removeActivity("title");
//	assert(service.size() == 0);
//	try {
//		service.removeActivity("title");
//		assert(false);
//	}
//	catch (ServiceException) { assert(true); }
//	service.addActivity("title", "description", "type", "1");
//	service.updateActivity("title", "new", "new", "2");
//	try {
//		service.updateActivity("asd", "asd", "asd", "2");
//		assert(false);
//	}
//	catch (ServiceException) { assert(true); }
//	std::vector<Activity> activities = service.getActivities();
//	assert(activities[0].getDescription() == "new");
//	assert(activities[0].getType() == "new");
//	assert(activities[0].getDuration() == 2);
//	Activity activity = service.getActivity("title");
//	assert(activity.getDescription() == "new");
//
//	service.addActivity("title1", "description", "da", "5");
//	service.addActivity("title2", "zzz", "nu", "4");
//	service.addActivity("title3", "description", "da", "2");
//	service.addActivity("title4", "asd", "da", "3");
//	std::vector<Activity> descriptionActivities = service.descriptionFilter("description");
//	assert(descriptionActivities.size() == 2);
//	assert(descriptionActivities[0].getTitle() == "title1");
//	assert(descriptionActivities[1].getTitle() == "title3");
//
//	std::vector<Activity> typeActivities = service.typeFilter("da");
//	assert(typeActivities.size() == 3);
//	assert(descriptionActivities[0].getTitle() == "title1");
//	assert(descriptionActivities[1].getTitle() == "title3");
//
//	service.removeActivity("title");
//
//	assert(service.size() == 4);
//
//	std::vector<Activity> titleSorted = service.titleSort();
//	assert(titleSorted[0].getTitle() == "title1");
//	assert(titleSorted[1].getTitle() == "title2");
//	assert(titleSorted[2].getTitle() == "title3");
//	assert(titleSorted[3].getTitle() == "title4");
//
//	std::vector<Activity> descriptionSorted = service.descriptionSort();
//	assert(descriptionSorted[0].getTitle() == "title4");
//	assert(descriptionSorted[1].getTitle() == "title1");
//	assert(descriptionSorted[2].getTitle() == "title3");
//	assert(descriptionSorted[3].getTitle() == "title2");
//
//	std::vector<Activity> typeDurationSorted = service.typeDurationSort();
//	assert(typeDurationSorted[0].getTitle() == "title3");
//	assert(typeDurationSorted[1].getTitle() == "title4");
//	assert(typeDurationSorted[2].getTitle() == "title1");
//	assert(typeDurationSorted[3].getTitle() == "title2");
//
//	service.generateCurrent("3");
//	assert(service.getCurrent().size() == 3);
//	try {
//		service.generateCurrent("");
//		assert(false);
//	}
//	catch (ServiceException) {
//		assert(true);
//	}
//	service.clearCurrent();
//	assert(service.getCurrent().size() == 0);
//	try {
//		service.addCurrent("");
//		assert(false);
//	}
//	catch (ServiceException) {
//		assert(true);
//	}
//	try {
//		service.addCurrent("inexistenta");
//		assert(false);
//	}
//	catch (ServiceException) {
//		assert(true);
//	}
//	service.addCurrent("title1");
//	assert(service.getCurrent().size() == 1);
//	try {
//		service.addCurrent("title1");
//		assert(false);
//	}
//	catch (ServiceException) {
//		assert(true);
//	}
//}
//
//void testUndo() {
//	std::ofstream out("test.txt");
//	out << "";
//	Service service = Service("test.txt");
//	service.addActivity("asd", "asd", "asd", "1");
//	service.undo();
//	assert(service.size() == 0);
//	try {
//		service.undo();
//		assert(false);
//	}
//	catch (ServiceException) {
//		assert(true);
//	}
//	service.addActivity("asd", "asd", "asd", "1");
//	service.updateActivity("asd", "abc", "abc", "2");
//	service.undo();
//	assert(service.getActivity("asd").getDescription() == "asd");
//	service.removeActivity("asd");
//	assert(service.size() == 0);
//	service.undo();
//	assert(service.size() == 1);
//	service.exportRepoCVS("testCVS.cvs");
//	service.exportRepoHTML("testHTML.html");
//
//}
//
//void runTests() {
//	testActivity();
//	testRepository();
//	testService();
//	testUndo();
//}