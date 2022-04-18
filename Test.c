#pragma once
#include "Elevi.h"
#include "Repo.h"
#include "Valid.h"
#include "Service.h"
#include "Test.h"

void Test() {
	test_init_elev();
	test_sets_elev();
	test_sets_elev();
	//test_copyElev();
	test_valid_name();
	test_valid_txt();
	test_valid_nota();

	test_create_repo();
	test_find_repo();
	test_delete_from_repo();
	test_repo_add();
	test_add_more_repo();
	test_modify_repo();
	test_sort_nume_repo();
	test_sort_nume2_repo();
	test_sort_scor_repo();
	test_sort_scor2_repo();
	//testCopyList();

	test_servCreate();
	test_servAdd();
	test_servAddmore();
	test_servFind();
	test_servUpdate();
	test_servDell();
	test_servSort();
	testUndo();
}